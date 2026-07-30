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
This class inherits from :class:`~openturns.ActiveLearningReliabilityFunction` and implements the calculation of the "U" function for reliability analysis.

Let consider :math:`\vect{X}` a sample of dimension :math:`\inputDim` that is returned by a reliability simulation algorithm, :math:`T` the threshold defining the limit state of the reliability problem, and :math:`hat{g}(\cdot)` and :math:`hat{\sigma}(\cdot)` respectively the conditional mean and conditional standard deviation of the Gaussian Process Regressor used in the :class:`~openturns.ActiveLearningReliabilityAlgorithm`. 


The "U" function  :math:`U: \Rset^\inputDim \rightarrow \Rset^+` is defined as :

.. math::

   U(\mathbf{x}) = \frac{|T-\hat{g}(\vect{x})|}{\hat{\sigma}(\vect{x})}

The sample that minimizes the "U" function will be selected for the refinement of the Gaussian Process Regressor.
"

// ---------------------------------------------------------------------------

%feature("docstring") OT::ActiveLearningUFunction::computeAsScalar
"Computation of the active learning criterion.

Parameters
----------
inputSample : :class:`~openturns.Point`
    Gaussian Process Regressor Result
    
Returns
-------
value : Scalar
    Value of the U function for the considered sample.
"
