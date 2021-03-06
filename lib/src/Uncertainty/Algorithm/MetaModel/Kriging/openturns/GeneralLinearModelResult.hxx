//                                               -*- C++ -*-
/**
 *  @brief The result of a linear model estimation
 *
 *  Copyright 2005-2019 Airbus-EDF-IMACS-Phimeca
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
#ifndef OPENTURNS_GENERALLINEARMODELRESULT_HXX
#define OPENTURNS_GENERALLINEARMODELRESULT_HXX

#include "openturns/MetaModelResult.hxx"
#include "openturns/CovarianceModel.hxx"
#include "openturns/Sample.hxx"
#include "openturns/Collection.hxx"
#include "openturns/PersistentCollection.hxx"
#include "openturns/Basis.hxx"
#include "openturns/Function.hxx"
#include "openturns/Process.hxx"
#include "openturns/HMatrix.hxx"
#include "openturns/Basis.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class GeneralLinearModelResult
 *
 * The result of a generalized linear model evaluation
 */

class OT_API GeneralLinearModelResult
  : public MetaModelResult
{
  CLASSNAME

public:

  typedef Collection<Point> PointCollection;
  typedef PersistentCollection<Point> PointPersistentCollection;
  typedef Collection<Basis> BasisCollection;
  typedef PersistentCollection<Basis> BasisPersistentCollection;

  /** Default constructor */
  GeneralLinearModelResult();

  /** Parameter constructor without any cholesky factor*/
  GeneralLinearModelResult(const Sample & inputData,
                           const Sample & outputData,
                           const Function & metaModel,
                           const Point & residuals,
                           const Point & relativeErrors,
                           const BasisCollection & basis,
                           const PointCollection & trendCoefficients,
                           const CovarianceModel & covarianceModel,
                           const Scalar optimalLogLikelihood);

  /** Parameter constructor with Cholesky factor (Lapack)*/
  GeneralLinearModelResult(const Sample & inputData,
                           const Sample & outputData,
                           const Function & metaModel,
                           const Point & residuals,
                           const Point & relativeErrors,
                           const BasisCollection & basis,
                           const PointCollection & trendCoefficients,
                           const CovarianceModel & covarianceModel,
                           const Scalar optimalLogLikelihood,
                           const TriangularMatrix & covarianceCholeskyFactor,
                           const HMatrix & covarianceHMatrix);

  /** Virtual constructor */
  GeneralLinearModelResult * clone() const;

  /** String converter */
  String __repr__() const;
  String __str__(const String & offset = "") const;

  /** Trend basis accessor */
  BasisCollection getBasisCollection() const;

  /** Trend coefficients accessor */
  PointCollection getTrendCoefficients() const;

  /** Conditional covariance models accessor */
  CovarianceModel getCovarianceModel() const;

  /** Transformation accessor */
  Function getTransformation() const;
  void setTransformation(const Function & transformation);

  /** process accessor */
  Process getNoise() const;

  /** Optimal likelihood accessor */
  Scalar getOptimalLogLikelihood() const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);


protected:

  // KrigingAlgorithm::run could ask for the Cholesky factor
  friend class KrigingAlgorithm;
  /** Method that returns the covariance factor - lapack */
  TriangularMatrix getCholeskyFactor() const;

  /** Method that returns the covariance factor - hmat */
  HMatrix getHMatCholeskyFactor() const;

  // Return input sample transformed
  Sample getInputTransformedSample() const;

private:

  /** inputData should be keeped*/
  Sample inputData_;

  /** input transformed data: store data*/
  Sample inputTransformedData_;

  /** inputTransformation ==> iso-probabilistic transformation */
  Function inputTransformation_;

  /** Boolean transformation */
  Bool hasTransformation_;

  /** The trend basis */
  BasisPersistentCollection basis_;

  /** The trend coefficients */
  PointPersistentCollection beta_;

  /** The covariance model */
  CovarianceModel covarianceModel_;

  /** The optimal log-likelihood value */
  Scalar optimalLogLikelihood_;

  /** Boolean for cholesky. */
  Bool hasCholeskyFactor_;

  /** Cholesky factor  */
  mutable TriangularMatrix covarianceCholeskyFactor_;

  /** Cholesky factor when using hmat-oss/hmat */
  mutable HMatrix covarianceHMatrix_;

} ; /* class GeneralLinearModelResult */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_KRIGINGRESULT_HXX */
