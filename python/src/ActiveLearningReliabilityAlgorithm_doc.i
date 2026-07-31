%feature("docstring") OT::ActiveLearningReliabilityAlgorithm
"Active learning reliability algorithm.

Parameters
----------
reliabilityThreshold : float
    Reliability analysis threshold.

learningThreshold : float
    Threshold used to check the active learning convergence.


See also
--------
ActiveLearningGMMFunction, ActiveLearningEFFFunction, ActiveLearningUFunction, ActiveLearningReliabilityResult

Notes
-----
This class is a base class for all the active learning criteria for reliability analysis.

The principle is to evaluate candidate samples on an active learning (also known as infill) criterion to identify the sample that is the most relevant for the metamodel update.

A ActiveLearningReliabilityFunction object can be created only through its derivative classes,
:class:`~openturns.ActiveLearningUFunction`, :class:`~openturns.ActiveLearningEFFFunction` or :class:`~openturns.ActiveLearningGMMFunction`.
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::setConvergenceCriterion
"Accessor to convergence criterion.

Parameters
----------
convergenceCriterion : int, optional
    Selection flag:

    - PROBABILITY_UNCERTAINTY : convergence based on the uncertainty of probability estimate due to the Gaussian process
    - RELIABILITY_INDEX_UNCERTAINTY : convergence based on the uncertainty of reliability index estimate due to the Gaussian process
    - ACTIVE_LEARNING : convergence based on the active learning
    - PROBABILITY_STABILITY : convergence based on the stability of probability estimate between two active learning iterations
    - RELIABILITY_INDEX_STABILITY : convergence based on the stability of probability estimate between two active learning iterations
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::setConvergenceCriterionThreshold
"Accessor to the convergence uncertainty threshold. This parameter is used to check the convergence (regarding probabiliy uncertainty, reliability index uncertainty, probability stability or reliability index stability.
Parameters
----------
convergenceCriterionThreshold : Scalar
   Threshold to check is active learning reliability algorithm has converged

Notes
-----
This unique accessor allows one to define the threshold to check convergence in case `PROBABILITY_UNCERTAINTY`, `RELIABILITY_INDEX_UNCERTAINTY`,
`PROBABILITY_STABILITY` or `RELIABILITY_INDEX_STABILITY` are selected in method `setConvergenceCriterion`
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::setConvergenceUncertaintyFactor
"Accessor to the convergence uncertainty factor. This parameter is used to determine the confidence interval of probability due to Gaussian process uncertainty.

Parameters
-------
convergenceUncertaintyFactor : Scalar
   Convergence uncertainty factor

Notes
-----
This parameter :math:`k` is used to determine the confidence interval of probability due to Gaussian process uncertainty. This term is a multiplicative factor of  the standard deviation of the Gaussian process to compute the confidence interval. Let consider :math:`\inputRV` the input random vector and :math:`T` the threshold defining the limit state of the reliability problem, and :math:`\hat{\model}(\cdot)` and :math:`\hat{\sigma}(\cdot)` respectively the mean and standard deviation of the conditioned Gaussian process used in the :class:`~openturns.ActiveLearningReliabilityAlgorithm`. The convergence uncertainty factor is used when the convergence criterion is equal to PROBABILITY_UNCERTAINTY and RELIABILITY_INDEX_UNCERTAINTY and computes the probability for :math:`\hat{\model}(\cdot)+/- k \hat{\sigma}(\cdot)` instead of :math:`\hat{\model}(\cdot)`
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::setSimulationBudget
"Accessor to maximal simulation budget

Parameters
----------
simulationBudget : int
   Maximal simulation budget
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::setSimulationAlgorithmSeed
"Accessor to random generator seed for the simulation algorithm

Parameters
----------
seed : int
   Seed of the random generator
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::getSimulationAlgorithmSeed
"Accessor to random generator seed for the simulation algorithm

Returns
-------
seed : int
   Seed of the random generator
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::getFunctionCallNumber
"Accessor to number of limit state function calls

Returns
-------
functionCall : int
   Number of limit state function calls
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::getInputDoE
"Accessor to Design of experiments input sample

Returns
-------
functionCall : :class:`~openturns.Sample`
   Design of experiments input sample
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::getOutputDoE
"Accessor to Design of experiments output sample

Returns
-------
functionCall : :class:`~openturns.Sample`
   Design of experiments output sample
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::getResult
"Accessor to Active Reliability algorithm result

Returns
-------
functionCall : :class:`~openturns.ActiveLearningReliabilityResult`
   Result of active learning algorithm
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::setResult
"Accessor to Active Reliability algorithm result

Parameters
----------
functionCall : :class:`~openturns.ActiveLearningReliabilityResult`
   Result of active learning algorithm
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::checkConvergenceProbabilityWithUncertainty
"Convergence check based on probability uncertainty due to Gaussian process

Returns
-------
convergenceStatus : Bool
   Convergence status
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::checkConvergenceReliabilityIndexWithUncertainty
"Convergence check based on reliability index uncertainty due to Gaussian process

Returns
-------
convergenceStatus : Bool
   Convergence status
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::checkConvergenceStability
"Convergence check based on reliability index uncertainty due to Gaussian process

Parameters
----------
currentValue : :class:`~openturns.Scalar`
   Current value
pastValue : :class:`~openturns.Scalar`
   Previous value

Returns
-------
convergenceStatus : Bool
   Convergence status
"

// ---------------------------------------------------------------------------
%feature("docstring") OT::ActiveLearningReliabilityAlgorithm::computeProbabilityWithUncertainty
"Computation of probability confidence interval  due to Gaussian process uncertainty

Returns
-------
probaCI : :class:`~openturns.Point`
   Probability confidence interval due to the Gaussian process uncertainty  
"
