#! /usr/bin/env python

import openturns as ot

# from math import *

ot.TESTPREAMBLE()


def cleanScalar(inScalar):
    if abs(inScalar) < 1.0e-10:
        inScalar = 0.0
    return inScalar


#
# Physical model
#

inputFunction = ot.Description(2)
inputFunction[0] = "u1"
inputFunction[1] = "u2"

formulas = ot.Description(1)
formulas[0] = "3.0 - u1 * u2"

limitState = ot.SymbolicFunction(inputFunction, formulas)

dim = limitState.getInputDimension()

#
# Probabilistic model
#
ot.RandomGenerator.SetSeed(1)

mean = ot.Point(dim, 0.0)

sigma = ot.Point(dim, 1.0)

R = ot.CorrelationMatrix(dim)
myDistribution = ot.Normal(mean, sigma, R)

#
# Limit state
#

vect = ot.RandomVector(myDistribution)

output = ot.CompositeRandomVector(limitState, vect)

myEvent = ot.ThresholdEvent(output, ot.Less(), 0.0)

#
# Computation
#

#
# FORM/SORM Abdo Rackwitz
myAbdoRackwitz = ot.AbdoRackwitz()
myAbdoRackwitz.setMaximumIterationNumber(100)
myAbdoRackwitz.setMaximumAbsoluteError(1.0e-10)
myAbdoRackwitz.setMaximumRelativeError(1.0e-10)
myAbdoRackwitz.setMaximumResidualError(1.0e-10)
myAbdoRackwitz.setMaximumConstraintError(3.0e-10)
myAbdoRackwitz.setStartingPoint([1.0] * dim)

myAlgoAR = ot.FORM(myAbdoRackwitz, myEvent)
myAlgoAR2 = ot.SORM(myAbdoRackwitz, myEvent)

myAlgoAR.run()
myAlgoAR2.run()

resultAR = ot.FORMResult(myAlgoAR.getResult())
resultAR2 = ot.SORMResult(myAlgoAR2.getResult())

#
# Monte Carlo
CoV_MC = 0.1
myMC = ot.ProbabilitySimulationAlgorithm(myEvent, ot.MonteCarloExperiment())
myMC.setMaximumOuterSampling(8000)
myMC.setBlockSize(1)
myMC.setMaximumCoefficientOfVariation(CoV_MC)
myMC.run()

#
# LHS
CoV_LHS = 0.1
myLHS = ot.ProbabilitySimulationAlgorithm(myEvent, ot.LHSExperiment())
myLHS.setMaximumOuterSampling(8000)
myLHS.setBlockSize(1)
myLHS.setMaximumCoefficientOfVariation(CoV_LHS)
myLHS.run()

#
# Results
#

#
# FORM/SORM Abdo Rackwitz
PfAR = resultAR.getEventProbability()
Beta_generalizedAR = resultAR.getGeneralisedReliabilityIndex()
u_starAR = resultAR.getStandardSpaceDesignPoint()
x_starAR = resultAR.getPhysicalSpaceDesignPoint()
PtAR = resultAR.getIsStandardPointOriginInFailureSpace() and "true" or "false"
gammaAR = resultAR.getImportanceFactors()
beta_hasoferAR = resultAR.getHasoferReliabilityIndex()
SensitivityAR = resultAR.getEventProbabilitySensitivity()

PFBreitAR2 = resultAR2.getEventProbabilityBreitung()
BetaBreitAR2 = resultAR2.getGeneralisedReliabilityIndexBreitung()
PFHBAR2 = resultAR2.getEventProbabilityHohenbichler()
BetaHBAR2 = resultAR2.getGeneralisedReliabilityIndexHohenbichler()
PFTvedtAR2 = resultAR2.getEventProbabilityTvedt()
BetaTvedtAR2 = resultAR2.getGeneralisedReliabilityIndexTvedt()
CurvAR2 = resultAR2.getSortedCurvatures()
u_starAR2 = resultAR2.getStandardSpaceDesignPoint()
x_starAR2 = resultAR2.getPhysicalSpaceDesignPoint()
PtAR2 = resultAR2.getIsStandardPointOriginInFailureSpace() and "true" or "false"
gammaAR2 = resultAR2.getImportanceFactors()
beta_hasoferAR2 = resultAR2.getHasoferReliabilityIndex()

#
# Monte Carlo
ResultMC = myMC.getResult()
PFMC = ResultMC.getProbabilityEstimate()
CVMC = ResultMC.getCoefficientOfVariation()
Variance_PF_MC = ResultMC.getVarianceEstimate()
length90MC = ResultMC.getConfidenceLength(0.90)

#
# LHS
ResultLHS = myLHS.getResult()
PFLHS = ResultLHS.getProbabilityEstimate()
CVLHS = ResultLHS.getCoefficientOfVariation()
Variance_PF_LHS = ResultLHS.getVarianceEstimate()
length90LHS = ResultLHS.getConfidenceLength(0.90)

#

#
# Outputs
#
print("")
print("")
print(
    "************************************************************************************************"
)
print(
    "************************************** FORM ABDO RACKWITZ **************************************"
)
print(
    "************************************************************************************************"
)
print("event probability = %.5e" % PfAR)
print("generalized reliability index = %.5f" % Beta_generalizedAR)
print(
    "************************************************************************************************"
)
for i in range(u_starAR.getDimension()):
    print("standard space design point = %.5f" % u_starAR[i])
print(
    "************************************************************************************************"
)
for i in range(x_starAR.getDimension()):
    print("physical space design point = %.5f" % x_starAR[i])
print(
    "************************************************************************************************"
)
print("is standard point origin in failure space? ", PtAR)
print(
    "************************************************************************************************"
)
for i in range(gammaAR.getDimension()):
    print("importance factors = %.5f" % gammaAR[i])
print(
    "************************************************************************************************"
)
print("Hasofer reliability index = %.5f" % beta_hasoferAR)
print(
    "************************************************************************************************"
)
for i in range(SensitivityAR.getSize()):
    for j in range(SensitivityAR[i].getDimension()):
        print("Pf sensitivity = %.5f" % SensitivityAR[i][j])
print(
    "************************************************************************************************"
)
print("")
print(
    "************************************************************************************************"
)

print(
    "************************************** SORM ABDO RACKWITZ **************************************"
)
print(
    "************************************************************************************************"
)
print("Breitung event probability = %.5e" % PFBreitAR2)
print("Breitung generalized reliability index = %.5f" % BetaBreitAR2)
print("Hohenbichler event probability = %.5e" % PFHBAR2)
print("Hohenbichler generalized reliability index = %.5f" % BetaHBAR2)
print("Tvedt event probability = %.5e" % PFTvedtAR2)
print("Tvedt generalized reliability index = %.5f" % BetaTvedtAR2)
print(
    "************************************************************************************************"
)
for i in range(CurvAR2.getDimension()):
    print("sorted curvatures = %.5f" % cleanScalar(CurvAR2[i]))
print(
    "************************************************************************************************"
)
for i in range(u_starAR2.getDimension()):
    print("standard space design point = %.5f" % u_starAR2[i])
print(
    "************************************************************************************************"
)
for i in range(x_starAR2.getDimension()):
    print("physical space design point = %.5f" % x_starAR2[i])
print(
    "************************************************************************************************"
)
print(
    "************************************************************************************************"
)
print("is standard point origin in failure space? ", PtAR2)
print(
    "************************************************************************************************"
)
for i in range(gammaAR2.getDimension()):
    print("importance factors = %.5f" % gammaAR2[i])
print(
    "************************************************************************************************"
)
print("Hasofer reliability index = %.5f" % beta_hasoferAR2)
print(
    "************************************************************************************************"
)
print("")
print(
    "************************************************************************************************"
)
print(
    "**************************************** MONTE CARLO *******************************************"
)
print(
    "************************************************************************************************"
)
print("Pf estimation = %.5e" % PFMC)
print("Pf Variance estimation = %.5e" % Variance_PF_MC)
print("CoV = %.5f" % CVMC)
print("90% Confidence Interval =", "%.5e" % length90MC)
print(
    "CI at 90% =[",
    "%.5e" % (PFMC - 0.5 * length90MC),
    "; %.5e" % (PFMC + 0.5 * length90MC),
    "]",
)
print(
    "************************************************************************************************"
)
print("")
print(
    "************************************************************************************************"
)
print(
    "******************************************* L H S **********************************************"
)
print(
    "************************************************************************************************"
)
print("Pf estimation = %.5e" % PFLHS)
print("Pf Variance estimation = %.5e" % Variance_PF_LHS)
print("CoV = %.5f" % CVLHS)
print("90% Confidence Interval =", "%.5e" % length90LHS)
print(
    "CI at 90% =[",
    "%.5e" % (PFLHS - 0.5 * length90LHS),
    "; %.5e" % (PFLHS + 0.5 * length90LHS),
    "]",
)
print(
    "************************************************************************************************"
)
print("")
