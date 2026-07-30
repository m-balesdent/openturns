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
:class:`~openturns.ActiveLearningUFunction`, :class:`~openturns.ActiveLearningEFFFunction` or :class:`~openturns.ActiveLearningGMMFunction`."

