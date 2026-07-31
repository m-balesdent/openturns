%feature("docstring") OT::ActiveLearningUFunction
"Active learning criterion for reliability analysis implementing the "U" function.

Parameters
----------
reliabilityThreshold : float
    Reliability analysis threshold.

learningThreshold : float
    Threshold used to check the active learning convergence.


See also
--------
ActiveLearningGMMFunction, ActiveLearningEFFFunction, ActiveLearningReliabilityFunction, ActiveLearningReliabilityAlgorithm

Notes
-----
This class inherits from :class:`~openturns.ActiveLearningReliabilityFunction` and implements the calculation of the "U" function for reliability analysis. The sample that minimizes the "U" function will be selected for the refinement of the Gaussian Process Regressor.

Let consider :math:`\inputRV` a sample of dimension :math:`\inputDim` that is returned by a reliability simulation algorithm, :math:`T` the threshold defining the limit state of the reliability problem, and :math:`\hat{\model}(\cdot)` and :math:`\hat{\sigma}(\cdot)` respectively the mean and standard deviation of the conditioned Gaussian process used in the :class:`~openturns.ActiveLearningReliabilityAlgorithm`. The "U" function  :math:`U: \Rset^\inputDim \rightarrow \Rset^+` is defined as :

.. math::

   U(\vect{x}) = \frac{|T - \hat{\model}(\vect{x})|}{\hat{\sigma}(\vect{x})}

"

// ---------------------------------------------------------------------------

%feature("docstring") OT::ActiveLearningUFunction::computeAsScalar
"Computation of the active learning criterion.

Parameters
----------
inputSample : :class:`~openturns.Point`
    Point on which the infill criterion will be computed
    
Returns
-------
value : Scalar
    Value of the U function for the considered sample.
"
