// SWIG file DistributionImplementation.i

// do not pass argument by reference, return it as tuple item
%typemap(in, numinputs=0) OT::Sample & gridOut ($*ltype temp) %{ temp = OT::Sample(); $1 = &temp; %}
%typemap(argout) OT::Sample & gridOut %{ $result = OT::AppendOutput($result, SWIG_NewPointerObj(new OT::Sample(*$1), SWIGTYPE_p_OT__Sample,  SWIG_POINTER_OWN)); %}

%typemap(in, numinputs=0) OT::Point & marginalProbOut ($*ltype temp) %{ temp = OT::Point(); $1 = &temp; %}
%typemap(argout) OT::Point & marginalProbOut %{ $result = OT::AppendOutput($result, SWIG_NewPointerObj(new OT::Point(*$1), SWIGTYPE_p_OT__Point,  SWIG_POINTER_OWN)); %}

%typemap(in, numinputs=0) OT::Point & thresholdOut ($*ltype temp) %{ temp = OT::Point(); $1 = &temp; %}
%typemap(argout) OT::Point & thresholdOut %{ $result = OT::AppendOutput($result, SWIG_NewPointerObj(new OT::Point(*$1), SWIGTYPE_p_OT__Point,  SWIG_POINTER_OWN)); %}

%typemap(in, numinputs=0) OT::Scalar & marginalProbOut ($*ltype temp) %{ temp = -1.0; $1 = &temp; %}
%typemap(argout) OT::Scalar & marginalProbOut %{ $result = OT::AppendOutput($result, PyFloat_FromDouble(*$1)); %}

%typemap(in, numinputs=0) OT::Scalar & thresholdOut ($*ltype temp) %{ temp = -1.0; $1 = &temp; %}
%typemap(argout) OT::Scalar & thresholdOut %{ $result = OT::AppendOutput($result, PyFloat_FromDouble(*$1)); %}


%{
#include "openturns/DistributionImplementation.hxx"
%}

%include DistributionImplementation_doc.i

%ignore OT::DistributionImplementation::pow;
%ignore OT::DistributionImplementation::setWeight;
%ignore OT::DistributionImplementation::getWeight;
%ignore OT::DistributionImplementation::setParallel;
%ignore OT::DistributionImplementation::setQuantileEpsilon;
%ignore OT::DistributionImplementation::getQuantileEpsilon;
%ignore OT::DistributionImplementation::computeProbabilityGeneral;
%ignore OT::DistributionImplementation::computeProbabilityGeneral1D;
%ignore OT::DistributionImplementation::computeProbabilityContinuous;
%ignore OT::DistributionImplementation::computeProbabilityContinuous1D;
%ignore OT::DistributionImplementation::computeProbabilityDiscrete;


%include openturns/DistributionImplementation.hxx

namespace OT {

%extend DistributionImplementation {

DistributionImplementation(const DistributionImplementation & other) { return new OT::DistributionImplementation(other); } 

Distribution __rtruediv__(const Scalar s) { return s / (*self); }

Distribution __rdiv__(const Scalar s) { return s / (*self); }

Distribution __pow__(const Scalar s) { return self->pow(s); }

Distribution __sub__(const Scalar s)
{
 return *self - s;
}

Distribution __rsub__(const Scalar s)
{
  return (*self * (-1.0)) + s;
}

Distribution __neg__() { return -(*self); }

Distribution __add__(const Scalar s)
{
 return *self + s;
}

Distribution __radd__(const Scalar s)
{
  return *self + s;
}

Distribution __mul__(Scalar s)
{
  return (*self) * s;
}

Distribution __rmul__(Scalar s)
{
  return (*self) * s;
}



} }
