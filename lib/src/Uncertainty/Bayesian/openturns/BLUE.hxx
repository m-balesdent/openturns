//                                               -*- C++ -*-
/**
 *  @brief BLUE algorithm
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
#ifndef OPENTURNS_BLUE_HXX
#define OPENTURNS_BLUE_HXX

#include "openturns/OTprivate.hxx"
#include "openturns/CalibrationAlgorithmImplementation.hxx"
#include "openturns/Sample.hxx"
#include "openturns/Function.hxx"
#include "openturns/LeastSquaresMethod.hxx"
#include "openturns/ResourceMap.hxx"
#include "openturns/CovarianceMatrix.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class BLUE
 *
 * @brief The class implements the best linear unbiased estimator (BLUE) calibration
 *
 */
class OT_API BLUE
  : public CalibrationAlgorithmImplementation
{
  CLASSNAME
public:

  /** Default constructor */
  BLUE();

  /** Parameter constructor */
  BLUE(const Function & model,
       const Sample & inputObservations,
       const Sample & outputObservations,
       const Point & candidate,
       const CovarianceMatrix & parameterCovariance,
       const CovarianceMatrix & errorCovariance,
       const String & methodName = ResourceMap::GetAsString("BLUE-Method"));

  /** Parameter constructor */
  BLUE(const Sample & modelObservations,
       const Matrix & gradientObservations,
       const Sample & outputObservations,
       const Point & candidate,
       const CovarianceMatrix & parameterCovariance,
       const CovarianceMatrix & errorCovariance,
       const String & methodName = ResourceMap::GetAsString("BLUE-Method"));

  /** String converter */
  virtual String __repr__() const;

  /** Performs the actual computation. Must be overloaded by the actual calibration algorithm */
  virtual void run();

  /** Model observations accessor */
  Sample getModelObservations() const;

  /** Model gradient wrt the parameter accessor */
  Matrix getGradientObservations() const;

  /** Candidate accessor */
  Point getCandidate() const;

  /** Parameter covariance accessor */
  CovarianceMatrix getParameterCovariance() const;

  /** Error covariance accessor */
  CovarianceMatrix getErrorCovariance() const;

  /** Least squares method name accessor */
  String getMethodName() const;

  /* Here is the interface that all derived class must implement */

  /** Virtual constructor */
  virtual BLUE * clone() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(Advocate & adv);

private:
  /* The model observations */
  Sample modelObservations_;

  /* The model gradient wrt the parameter */
  Matrix gradientObservations_;

  /* The error covariance */
  CovarianceMatrix errorCovariance_;
  
  /* The least squares method name */
  String methodName_;

}; /* class BLUE */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_BLUE_HXX */