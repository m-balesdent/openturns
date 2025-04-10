//                                               -*- C++ -*-
/**
 * @brief This class binds a Python object to an OpenTURNS' RandomVector
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

#include "openturns/PythonRandomVector.hxx"
#include "openturns/OSS.hxx"
#include "openturns/Description.hxx"
#include "openturns/PythonWrappingFunctions.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/Exception.hxx"

BEGIN_NAMESPACE_OPENTURNS


CLASSNAMEINIT(PythonRandomVector)

static const Factory<PythonRandomVector> Factory_PythonRandomVector;



/* Default constructor */
PythonRandomVector::PythonRandomVector()
  : RandomVectorImplementation(),
    pyObj_(0)
{
  // Nothing to do
}


/* Constructor from Python object*/
PythonRandomVector::PythonRandomVector(PyObject * pyObject)
  : RandomVectorImplementation(),
    pyObj_(pyObject)
{
  if ( !PyObject_HasAttrString( pyObj_, const_cast<char *>("getRealization") ) ) throw InvalidArgumentException(HERE) << "Error: the given object does not have a getRealization() method.";

  Py_XINCREF( pyObj_ );

  // Set the name of the object as its Python classname
  ScopedPyObjectPointer cls(PyObject_GetAttrString ( pyObj_,
                            const_cast<char *>( "__class__" ) ));
  ScopedPyObjectPointer name(PyObject_GetAttrString( cls.get(),
                             const_cast<char *>( "__name__" ) ));

  setName( checkAndConvert< _PyString_, String >(name.get()) );

  const UnsignedInteger dimension = getDimension();
  Description description(dimension);
  ScopedPyObjectPointer desc(PyObject_CallMethod ( pyObj_,
                             const_cast<char *>( "getDescription" ),
                             const_cast<char *>( "()" ) ));
  if ( ( desc.get() != NULL )
       && PySequence_Check( desc.get() )
       && ( PySequence_Size( desc.get() ) == static_cast<SignedInteger>(dimension) ) )
  {
    description = convert< _PySequence_, Description >( desc.get() );
  }
  else for (UnsignedInteger i = 0; i < dimension; ++i) description[i] = (OSS() << "x" << i);
  setDescription(description);
}

/* Virtual constructor */
PythonRandomVector * PythonRandomVector::clone() const
{
  return new PythonRandomVector(*this);
}

/* Copy constructor */
PythonRandomVector::PythonRandomVector(const PythonRandomVector & other)
  : RandomVectorImplementation(other),
    pyObj_()
{
  ScopedPyObjectPointer pyObjClone(deepCopy(other.pyObj_));
  pyObj_ = pyObjClone.get();
  Py_XINCREF(pyObj_);
}

/* Copy assignment operator */
PythonRandomVector & PythonRandomVector::operator=(const PythonRandomVector & rhs)
{
  if (this != &rhs)
  {
    RandomVectorImplementation::operator=(rhs);
    ScopedPyObjectPointer pyObjClone(deepCopy(rhs.pyObj_));
    pyObj_ = pyObjClone.get();
    Py_XINCREF(pyObj_);
  }
  return *this;
}

/* Destructor */
PythonRandomVector::~PythonRandomVector()
{
  Py_XDECREF(pyObj_);
}

/* Comparison operator */
Bool PythonRandomVector::operator ==(const PythonRandomVector & ) const
{
  return true;
}

/* String converter */
String PythonRandomVector::__repr__() const
{
  OSS oss;
  oss << "class=" << PythonRandomVector::GetClassName()
      << " name=" << getName()
      << " description=" << getDescription();
  return oss;
}

/* String converter */
String PythonRandomVector::__str__(const String & ) const
{
  OSS oss;
  oss << "class=" << PythonRandomVector::GetClassName()
      << " name=" << getName();
  return oss;
}


/* Here is the interface that all derived class must implement */


/* Accessor for input point dimension */
UnsignedInteger PythonRandomVector::getDimension() const
{
  ScopedPyObjectPointer result(PyObject_CallMethod ( pyObj_,
                               const_cast<char *>( "getDimension" ),
                               const_cast<char *>( "()" ) ));
  if ( result.isNull() )
  {
    handleException();
  }

  const UnsignedInteger dim = convert< _PyInt_, UnsignedInteger >(result.get());
  return dim;
}

Point PythonRandomVector::getRealization() const
{
  ScopedPyObjectPointer result(PyObject_CallMethod ( pyObj_,
                               const_cast<char *>( "getRealization" ),
                               const_cast<char *>( "()" ) ));
  if ( result.isNull() )
  {
    handleException();
  }
  const Point point(convert<_PySequence_, Point>(result.get()));
  if (point.getDimension() != getDimension()) throw InvalidDimensionException(HERE) << "PythonRandomVector realization has dimension " << point.getDimension() << ", expected " << getDimension();
  return point;
}


/* Numerical sample accessor */
Sample PythonRandomVector::getSample(const UnsignedInteger size) const
{
  Sample sample;

  if ( PyObject_HasAttrString( pyObj_, const_cast<char *>("getSample") ) )
  {
    ScopedPyObjectPointer methodName(convert< String, _PyString_>( "getSample" ));
    ScopedPyObjectPointer sizeArg(convert< UnsignedInteger, _PyInt_ >(size));
    ScopedPyObjectPointer result(PyObject_CallMethodObjArgs( pyObj_,
                                 methodName.get(),
                                 sizeArg.get(), NULL ));
    if ( result.get() )
    {
      sample = convert<_PySequence_, Sample>(result.get());
      if (sample.getSize() != size) throw InvalidDimensionException(HERE) << "PythonRandomVector sample has size " << sample.getSize() << ", expected " << size;
    }
  }
  else
  {
    sample = RandomVectorImplementation::getSample(size);
  }
  return sample;
}


/* Mean accessor */
Point PythonRandomVector::getMean() const
{
  ScopedPyObjectPointer result(PyObject_CallMethod ( pyObj_,
                               const_cast<char *>( "getMean" ),
                               const_cast<char *>( "()" ) ));
  if ( result.isNull() )
  {
    handleException();
  }

  const Point mean(convert<_PySequence_, Point>(result.get()));
  if (mean.getDimension() != getDimension()) throw InvalidDimensionException(HERE) << "PythonRandomVector mean has dimension " << mean.getDimension() << ", expected " << getDimension();
  return mean;
}

/* Covariance accessor */
CovarianceMatrix PythonRandomVector::getCovariance() const
{
  ScopedPyObjectPointer result(PyObject_CallMethod ( pyObj_,
                               const_cast<char *>( "getCovariance" ),
                               const_cast<char *>( "()" ) ));
  if ( result.isNull() )
  {
    handleException();
  }

  const CovarianceMatrix covariance(convert<_PySequence_, CovarianceMatrix>(result.get()));
  if (covariance.getDimension() != getDimension()) throw InvalidDimensionException(HERE) << "PythonRandomVector covariance matrix has dimension " << covariance.getDimension() << ", expected" << getDimension();

  return covariance;
}

Bool PythonRandomVector::isEvent() const
{
  if (PyObject_HasAttrString(pyObj_, const_cast<char *>("isEvent")))
  {
    ScopedPyObjectPointer result(PyObject_CallMethod ( pyObj_,
                                 const_cast<char *>( "isEvent" ),
                                 const_cast<char *>( "()" ) ));
    if (result.isNull())
    {
      handleException();
    }

    const Bool isEvent = checkAndConvert<_PyBool_, Bool>(result.get());
    return isEvent;
  }
  else
  {
    return RandomVectorImplementation::isEvent();
  }
}

/* Parameter accessor */
Point PythonRandomVector::getParameter() const
{
  if (PyObject_HasAttrString(pyObj_, const_cast<char *>("getParameter")))
  {
    ScopedPyObjectPointer callResult(PyObject_CallMethod( pyObj_,
                                     const_cast<char *>( "getParameter" ),
                                     const_cast<char *>( "()" ) ));
    if (callResult.isNull())
    {
      handleException();
    }
    const Point parameter(convert< _PySequence_, Point >(callResult.get()));
    return parameter;
  }
  else
  {
    // RandomVectorImplementation::getParameter throws
    return Point();
  }
}

/* Parameter accessor */
void PythonRandomVector::setParameter(const Point & parameter)
{
  if (PyObject_HasAttrString(pyObj_, const_cast<char *>("setParameter")))
  {
    ScopedPyObjectPointer methodName(convert< String, _PyString_ >("setParameter"));
    ScopedPyObjectPointer parameterArg(convert< Point, _PySequence_ >(parameter));
    ScopedPyObjectPointer callResult(PyObject_CallMethodObjArgs( pyObj_,
                                     methodName.get(),
                                     parameterArg.get(), NULL));
    if (callResult.isNull())
    {
      handleException();
    }
  }
}

/* Parameter description accessor */
Description PythonRandomVector::getParameterDescription() const
{
  if (PyObject_HasAttrString(pyObj_, const_cast<char *>("getParameterDescription")))
  {
    ScopedPyObjectPointer callResult(PyObject_CallMethod( pyObj_,
                                     const_cast<char *>( "getParameterDescription" ),
                                     const_cast<char *>( "()" ) ));
    if (callResult.isNull())
    {
      handleException();
    }
    Description parameterDescription(convert< _PySequence_, Description >(callResult.get()));
    return parameterDescription;
  }
  else
  {
    // RandomVectorImplementation::getParameterDescription throws
    return Description();
  }
}

/* Method save() stores the object through the StorageManager */
void PythonRandomVector::save(Advocate & adv) const
{
  RandomVectorImplementation::save(adv);

  pickleSave(adv, pyObj_);
}


/* Method save() reloads the object from the StorageManager */
void PythonRandomVector::load(Advocate & adv)
{
  RandomVectorImplementation::load(adv);

  pickleLoad(adv, pyObj_);
}


END_NAMESPACE_OPENTURNS
