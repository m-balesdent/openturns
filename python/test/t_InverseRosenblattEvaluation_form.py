#! /usr/bin/env python

import openturns as ot

ot.TESTPREAMBLE()

model = ot.SymbolicFunction(["x0", "x1", "x2", "x3"], ["-(6+x0^2-x1+x2+3*x3)"])
dim = model.getInputDimension()
marginals = [ot.Normal(5.0, 3.0) for i in range(dim)]
distribution = ot.JointDistribution(
    marginals, ot.BlockIndependentCopula([ot.ClaytonCopula(), ot.NormalCopula()])
)
# distribution = ot.Normal([5]*dim, [3]*dim, ot.CorrelationMatrix(dim))
# distribution = ot.JointDistribution(marginals, ot.IndependentCopula(dim))
distribution.setDescription(["marginal" + str(i) for i in range(dim)])
vect = ot.RandomVector(distribution)
output = ot.CompositeRandomVector(model, vect)
event = ot.ThresholdEvent(output, ot.Greater(), 0.0)
solver = ot.Cobyla()
solver.setMaximumCallsNumber(1000)
solver.setMaximumAbsoluteError(1.0e-10)
solver.setMaximumRelativeError(1.0e-10)
solver.setMaximumResidualError(1.0e-10)
solver.setMaximumConstraintError(1.0e-10)
solver.setStartingPoint(distribution.getMean())
algo = ot.FORM(solver, event)
algo.run()
result = algo.getResult()
hasoferReliabilityIndexSensitivity = result.getHasoferReliabilityIndexSensitivity()
print(hasoferReliabilityIndexSensitivity)
