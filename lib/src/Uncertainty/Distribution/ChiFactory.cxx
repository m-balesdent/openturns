//                                               -*- C++ -*-
/**
 *  @brief Factory for Chi distribution
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
#include "openturns/ChiFactory.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/SpecFunc.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(ChiFactory)

static const Factory<ChiFactory> Factory_ChiFactory;

/* Default constructor */
ChiFactory::ChiFactory()
  : DistributionFactoryImplementation()
{
  // Nothing to do
}

/* Virtual constructor */
ChiFactory * ChiFactory::clone() const
{
  return new ChiFactory(*this);
}

/* Here is the interface that all derived class must implement */

Distribution ChiFactory::build(const Sample & sample) const
{
  return buildAsChi(sample).clone();
}

Distribution ChiFactory::build(const Point & parameters) const
{
  return buildAsChi(parameters).clone();
}

Distribution ChiFactory::build() const
{
  return buildAsChi().clone();
}

Chi ChiFactory::buildAsChi(const Sample & sample) const
{
  const UnsignedInteger size = sample.getSize();
  if (size < 2) throw InvalidArgumentException(HERE) << "Error: cannot build a Chi distribution from a sample of size < 2";
  if (sample.getDimension() != 1) throw InvalidArgumentException(HERE) << "Error: can build a Chi distribution only from a sample of dimension 1, here dimension=" << sample.getDimension();
  const Scalar mean = sample.computeMean()[0];
  if (!SpecFunc::IsNormal(mean)) throw InvalidArgumentException(HERE) << "Error: cannot build a Chi distribution if data contains NaN or Inf";
  const Scalar xMin = sample.getMin()[0];
  const Scalar xMax = sample.getMax()[0];
  if (xMin == xMax) throw InvalidArgumentException(HERE) << "Error: cannot estimate a Chi distribution from a constant sample.";
  Scalar sumSquares = 0.0;
  for (UnsignedInteger i = 0; i < size; ++i)
  {
    const Scalar xI = sample(i, 0);
    sumSquares += xI * xI;
  }
  try
  {
    Chi result(sumSquares / size);
    result.setDescription(sample.getDescription());
    adaptToKnownParameter(sample, &result);
    return result;
  }
  catch (const InvalidArgumentException &)
  {
    throw InvalidArgumentException(HERE) << "Error: cannot estimate parameters of a Chi distribution from the given sample";
  }
}

Chi ChiFactory::buildAsChi(const Point & parameters) const
{
  try
  {
    Chi distribution;
    distribution.setParameter(parameters);
    return distribution;
  }
  catch (const InvalidArgumentException &)
  {
    throw InvalidArgumentException(HERE) << "Error: cannot build a Chi distribution from the given parameters";
  }
}

Chi ChiFactory::buildAsChi() const
{
  return Chi();
}

END_NAMESPACE_OPENTURNS
