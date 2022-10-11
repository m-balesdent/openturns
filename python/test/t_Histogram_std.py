#! /usr/bin/env python

import openturns as ot

ot.TESTPREAMBLE()

# Instantiate one distribution object
first = -1.5
l = [1.0, 0.7, 1.2, 0.9]
h = [0.5, 1.5, 3.5, 2.5]
t = [first]
f = list()
for i in range(len(l)):
    t.append(t[i] + l[i])
    f.append(h[i] * l[i])
distribution = ot.Histogram(t, f)
print("Distribution ", repr(distribution))
print("Distribution ", distribution)
distribution = ot.Histogram(first, l, h)
print("Distribution ", repr(distribution))
print("Distribution ", distribution)

# Is this distribution elliptical ?
print("Elliptical = ", distribution.isElliptical())

# Is this distribution continuous ?
print("Continuous = ", distribution.isContinuous())

# Test for realization of distribution
oneRealization = distribution.getRealization()
print("oneRealization=", repr(oneRealization))

# Test for sampling
size = 10000
oneSample = distribution.getSample(size)
print("oneSample first=", repr(oneSample[0]), " last=", repr(oneSample[1]))
print("mean=", repr(oneSample.computeMean()))
print("covariance=", repr(oneSample.computeCovariance()))

size = 100
for i in range(2):
    msg = ""
    if ot.FittingTest.Kolmogorov(
        distribution.getSample(size), distribution
    ).getBinaryQualityMeasure():
        msg = "accepted"
    else:
        msg = "rejected"
    print("Kolmogorov test for the generator, sample size=", size, " is", msg)
    size *= 10

# Define a point
point = ot.Point(distribution.getDimension(), 1.0)
print("Point= ", repr(point))

# Show PDF and CDF at point
eps = 1e-5
# derivative of PDF with regards its arguments
DDF = distribution.computeDDF(point)
print("ddf     =", repr(DDF))
# by the finite difference technique
print(
    "ddf (FD)=",
    repr(
        ot.Point(
            1,
            (
                distribution.computePDF(point + ot.Point(1, eps))
                - distribution.computePDF(point + ot.Point(1, -eps))
            )
            / (2.0 * eps),
        )
    ),
)

# PDF value
LPDF = distribution.computeLogPDF(point)
print("log pdf=%.6f" % LPDF)
PDF = distribution.computePDF(point)
print("pdf     =%.6f" % PDF)
# by the finite difference technique from CDF
print(
    "pdf (FD)=%.6f"
    % (
        (
            distribution.computeCDF(point + ot.Point(1, eps))
            - distribution.computeCDF(point + ot.Point(1, -eps))
        )
        / (2.0 * eps)
    )
)

# derivative of the PDF with regards the parameters of the distribution
CDF = distribution.computeCDF(point)
print("cdf=%.6f" % CDF)
CCDF = distribution.computeComplementaryCDF(point)
print("ccdf=%.6f" % CCDF)

# quantile
quantile = distribution.computeQuantile(0.95)
print("quantile=", repr(quantile))
print("cdf(quantile)=%.6f" % distribution.computeCDF(quantile))
# Get 95% survival function
inverseSurvival = ot.Point(distribution.computeInverseSurvivalFunction(0.95))
print("InverseSurvival=", repr(inverseSurvival))
print(
    "Survival(inverseSurvival)=%.6f"
    % distribution.computeSurvivalFunction(inverseSurvival)
)
print("entropy=%.6f" % distribution.computeEntropy())

# Confidence regions
interval, threshold = distribution.computeMinimumVolumeIntervalWithMarginalProbability(
    0.95
)
print("Minimum volume interval=", interval)
print("threshold=", ot.Point(1, threshold))
levelSet, beta = distribution.computeMinimumVolumeLevelSetWithThreshold(0.95)
print("Minimum volume level set=", levelSet)
print("beta=", ot.Point(1, beta))
interval, beta = distribution.computeBilateralConfidenceIntervalWithMarginalProbability(
    0.95
)
print("Bilateral confidence interval=", interval)
print("beta=", ot.Point(1, beta))
(
    interval,
    beta,
) = distribution.computeUnilateralConfidenceIntervalWithMarginalProbability(0.95, False)
print("Unilateral confidence interval (lower tail)=", interval)
print("beta=", ot.Point(1, beta))
(
    interval,
    beta,
) = distribution.computeUnilateralConfidenceIntervalWithMarginalProbability(0.95, True)
print("Unilateral confidence interval (upper tail)=", interval)
print("beta=", ot.Point(1, beta))

mean = distribution.getMean()
print("mean=", repr(mean))
covariance = distribution.getCovariance()
print("covariance=", repr(covariance))
parameters = distribution.getParametersCollection()
print("parameters=", repr(parameters))
print("Standard representative=", distribution.getStandardRepresentative())

testSize = 0
for i in range(testSize):
    q = ot.RandomGenerator().Generate()
    if fabs(q - distribution.computeCDF(distribution.computeQuantile(q))) > eps:
        print(
            "q=%.6f" % q,
            " quantile=%.6f" % distribution.computeQuantile(q)[0],
            " CDF(quantile)=%.6f"
            % distribution.computeCDF(distribution.computeQuantile(q)),
        )
