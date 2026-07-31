%feature("docstring") OT::ActiveLearningGMMFunction
"Active learning criterion for reliability analysis implementing the Generalized Max Min function.

Parameters
----------
reliabilityThreshold : float
    Reliability analysis threshold.

learningThreshold : float
    Threshold used to check the active learning convergence.
    
inputDistribution : Distribution
    Probability distribution of the input variables.

outputQuantileLevel : float
    Quantile level of the samples that will be considered for infill. Let :math:`\vect{X}_1,\dots,\vect{X}_N` the samples retrieved by the simulation algorithm, :math:`T` the event threshold and :math:`\hat{\model}(\cdot)` the mean of the conditioned Gaussian process.
    The selected samples for infill criterion evaluation are selected according to a criterion based on the quantile of the samples formed by the scaled outputs, given by :math:`\left\{\forall i \in \left\{1, \dots, N\right\} |\hat{\model}(\vect{X}_i) - T\|\right\}`
"
