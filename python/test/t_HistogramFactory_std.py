#! /usr/bin/env python

import openturns as ot
import openturns.testing as ott

ot.TESTPREAMBLE()

ot.Log.Show(ot.Log.WARN)

ll = [1.0, 0.7, 1.2, 0.9]
h = [0.5, 1.5, 3.5, 2.5]
distribution = ot.Histogram(-1.5, ll, h)
size = 10000
sample = distribution.getSample(size)
factory = ot.HistogramFactory()
estimatedDistribution = factory.build(sample)
print("distribution=", repr(distribution))
print("Estimated distribution=", repr(estimatedDistribution))
estimatedDistribution = factory.build()
print("Default distribution=", estimatedDistribution)
estimatedHistogram = factory.buildAsHistogram(sample)
print("Histogram          =", distribution)
print("Estimated histogram=", estimatedHistogram)
estimatedHistogram = factory.buildAsHistogram(sample, 0.1)
print("Histogram          =", distribution)
print("Estimated histogram=", estimatedHistogram)
estimatedHistogram = factory.buildAsHistogram(sample, 15)
print("Histogram          =", distribution)
print("Estimated histogram=", estimatedHistogram)
first = -2.0
width = ot.Point(5, 1.0)
estimatedHistogram = factory.buildAsHistogram(sample, first, width)
print("Estimated histogram=", estimatedHistogram)
estimatedHistogram = factory.buildAsHistogram()
print("Default histogram=", estimatedHistogram)

sample = ot.ChiSquare(0.0120637).getSample(32)
for useQuantile in [True, False]:
    print(
        "useQuantile=",
        useQuantile,
        ot.Point(1, ot.HistogramFactory().computeBandwidth(sample, useQuantile)),
    )

# from quantiles
ref_dist = ot.Normal()
lowerBound = -3.0
probabilities = [
    0.1,
    0.2,
    0.3,
    0.4,
    0.5,
    0.6,
    0.7,
    0.8,
    0.9,
    1.0 - ot.SpecFunc.ScalarEpsilon,
]
quantiles = [ref_dist.computeQuantile(pi)[0] for pi in probabilities]
inf_distribution = ot.HistogramFactory().buildFromQuantiles(
    lowerBound, probabilities, quantiles
)
inf_quantiles = [inf_distribution.computeQuantile(pi)[0] for pi in probabilities]
ott.assert_almost_equal(inf_quantiles, quantiles)

# samples with different scales, bandwidth should not be too small and blow up memory thanks to MaximumBinNumber
sample1 = ot.Uniform(-1e-10, 1e-10).getSample(100)
sample2 = ot.Uniform(-1, 1).getSample(5)
sample1.add(sample2)
dist = ot.HistogramFactory().build(sample1)
