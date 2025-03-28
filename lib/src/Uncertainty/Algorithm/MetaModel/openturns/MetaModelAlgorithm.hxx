//                                               -*- C++ -*-
/**
 *  @brief Implementation for metamodel algorithms
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
#ifndef OPENTURNS_METAMODELALGORITHM_HXX
#define OPENTURNS_METAMODELALGORITHM_HXX

#include "openturns/Point.hxx"
#include "openturns/Sample.hxx"
#include "openturns/Distribution.hxx"
#include "openturns/MetaModelResult.hxx"

BEGIN_NAMESPACE_OPENTURNS



/**
 * @class MetaModelAlgorithm
 *
 */

class OT_API MetaModelAlgorithm
  : public PersistentObject
{
  CLASSNAME
public:


  /** Default constructor */
  MetaModelAlgorithm();

  /** Constructor with parameters */
  MetaModelAlgorithm(const Sample & inputSample,
                     const Sample & outputSample);

  MetaModelAlgorithm(const Sample & inputSample,
                     const Point & weights,
                     const Sample & outputSample);

  MetaModelAlgorithm(const Sample & inputSample,
                     const Sample & outputSample,
                     const Distribution & distribution);

  MetaModelAlgorithm(const Sample & inputSample,
                     const Point & weights,
                     const Sample & outputSample,
                     const Distribution & distribution);

  /** Virtual constructor */
  MetaModelAlgorithm * clone() const override;

  /** String converter */
  String __repr__() const override;

  /** Distribution accessor */
  void setDistribution(const Distribution & distribution);
  Distribution getDistribution() const;

  /** Response surface computation */
  virtual void run();

  /** Sample accessors */
  Sample getInputSample() const;
  Sample getOutputSample() const;

  /** Weights accessor */
  Point getWeights() const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv) override;

  /** Recover the distribution */
  static Distribution BuildDistribution(const Sample & inputSample);

protected:
  /** Learning input sample */
  Sample inputSample_;

  /** Weights of the input sample */
  Point weights_;

  /** Learning output sample */
  Sample outputSample_;

  /** The input vector distribution */
  Distribution distribution_;

private:
  friend struct TestedDistribution;

}; /* class MetaModelAlgorithm */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_METAMODELALGORITHM_HXX */
