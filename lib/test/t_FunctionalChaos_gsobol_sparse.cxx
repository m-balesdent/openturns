//                                               -*- C++ -*-
/**
 *  @brief The test file of class LeastSquaresMetaModelSelection for standard methods
 *
 *  Copyright 2005-2025 Airbus-EDF-IMACS-ONERA-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "openturns/OT.hxx"
#include "openturns/OTtestcode.hxx"

using namespace OT;
using namespace OT::Test;

int main(int, char *[])
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);
  //   Log::Show( Log::Flags() | Log::INFO );

  // Problem parameters
  UnsignedInteger dimension = 8;

  // Reference analytical values
  Point a(dimension);
  a[0] = 1.0;
  a[1] = 2.0;
  a[2] = 5.0;
  a[3] = 10.0;
  a[4] = 20.0;
  a[5] = 50.0;
  a[6] = 100.0;
  a[7] = 500.0;

  // Create the gSobol function
  Description inputVariables(dimension);
  Description formula(1);
  formula[0] = "1.0";
  for (UnsignedInteger i = 0; i < dimension; ++i)
  {
    inputVariables[i] = (OSS() << "xi" << i);
    formula[0] = (OSS() << formula[0] << " * ((abs(4.0 * xi" << i << " - 2.0) + " << a[i] << ") / (1.0 + " << a[i] << "))");
  }

  SymbolicFunction model(inputVariables, formula);

  // Create the input distribution
  Collection<Distribution> marginalX(dimension);
  for ( UnsignedInteger i = 0; i < dimension; ++ i )
  {
    marginalX[i] = Uniform( 0.0, 1.0 );
  }
  JointDistribution distribution(marginalX);

  // Create the orthogonal basis
  Collection<OrthogonalUniVariatePolynomialFamily> polynomialCollection(dimension);
  for ( UnsignedInteger i = 0; i < dimension; ++ i )
  {
    polynomialCollection[i] = LegendreFactory();
  }
  const Scalar q = 0.4;
  HyperbolicAnisotropicEnumerateFunction enumerateFunction(dimension, q);
  OrthogonalProductPolynomialFactory productBasis(polynomialCollection, enumerateFunction);

  // design experiment
  UnsignedInteger samplingSize = 75;

  // build basis
  UnsignedInteger basisSize = enumerateFunction.getStrataCumulatedCardinal(30);

  // run algorithm
  Collection<FittingAlgorithm> listFittingAlgorithm;
  listFittingAlgorithm.add(KFold());
  listFittingAlgorithm.add(CorrectedLeaveOneOut());

  for (UnsignedInteger fittingAlgorithmIndex = 0; fittingAlgorithmIndex < listFittingAlgorithm.getSize(); ++ fittingAlgorithmIndex)
  {
    FixedStrategy adaptiveStrategy(productBasis, basisSize);
    FittingAlgorithm fittingAlgorithm( listFittingAlgorithm[fittingAlgorithmIndex] );
    const LeastSquaresStrategy projectionStrategy(LeastSquaresMetaModelSelectionFactory(LARS(), fittingAlgorithm));
    const LowDiscrepancyExperiment experiment(SobolSequence(), distribution, samplingSize);
    RandomGenerator::SetSeed(0);
    const Sample X(experiment.generate());
    const Sample Y(model(X));
    FunctionalChaosAlgorithm algo(X, Y, distribution, adaptiveStrategy, projectionStrategy);
    algo.run();

    FunctionalChaosResult result(algo.getResult());
    fullprint << "coeffs = " << result.getCoefficients() << std::endl;
  }




  return ExitCode::Success;
}
