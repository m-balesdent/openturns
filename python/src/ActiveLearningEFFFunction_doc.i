%feature("docstring") OT::ActiveLearningEFFFunction
"Active learning criterion for reliability analysis implementing the Expected Feasibility Function (EFF) function.

Parameters
----------
reliabilityThreshold : float
    Reliability analysis threshold.

learningThreshold : float
    Threshold used to check the active learning convergence.
"


// ---------------------------------------------------------------------------

%feature("docstring") OT::ActiveLearningEFFFunction::computeAsScalar
"Computation of the active learning criterion.

Parameters
----------
inputSample : :class:`~openturns.Point`
    Point on which the infill criterion will be computed.
    
Returns
-------
value : Scalar
    Value of the EFF function for the considered sample.
"

