"""
Trend computation
=================
"""

# %%
# In this example we are going to estimate a trend from a field.
#
# We note :math:`(\vect{x}_0, \dots, \vect{x}_{N-1})` the values of
# the initial field associated to the mesh :math:`\mathcal{M}` of :math:`\mathcal{D} \in \mathbb{R}^n`,
# where :math:`\vect{x}_i \in \mathbb{R}^d` and :math:`(\vect{x}^{stat}_0, \dots, \vect{x}^{stat}_{N-1})`
# the values of the resulting stationary field.
#
# The object :class:`~openturns.TrendFactory` allows one to estimate a trend and is built from:
#
# - a regression strategy that generates a basis using the Least Angle Regression method thanks to the object :class:`~openturns.LARS`,
# - a fitting algorithm that estimates the empirical error on each sub-basis using the leave one out strategy,
#   thanks to the object :class:`~openturns.CorrectedLeaveOneOut` or the k-fold algorithm thanks to the object :class:`~openturns.KFold`.
#
# Then, the trend transformation is estimated from the initial field :math:`(\vect{x}_0, \dots, \vect{x}_{N-1})`
# and a function basis :math:`\mathcal{B}` thanks to the method `build` of the object :class:`~openturns.TrendFactory`,
# which produces an object of type :class:`~openturns.TrendTransform`. This last object allows one to:
#
# - add the trend to a given field :math:`\vect{w}_0, \dots, \vect{w}_{N-1}` defined on the same mesh :math:`\mathcal{M}`:
#   the resulting field shares the same mesh than the initial field.
#   For example, it may be useful to add the trend to a realization of the stationary
#   process :math:`X_{stat}` in order to get a realization of the process :math:`X`
#
# - get the function :math:`f_{trend}` defined in that evaluates the trend thanks to the method `getEvaluation`;
#
# - create the inverse trend transformation in order to remove the trend the intiail field
#   :math:`(\vect{x}_0, \dots, \vect{x}_{N-1})` and to create the
#   resulting stationary field :math:`(\vect{x}^{stat}_0, \dots, \vect{x}^{stat}_{N-1})` such that:
#
# .. math::
#    \vect{x}^{stat}_i = \vect{x}_i - f_{trend}(\vect{t}_i)
#
# where :math:`\vect{t}_i` is the simplex associated to the value :math:`\vect{x}_i`.
#
# This creation of the inverse trend function :math:`-f_{trend}` is done thanks to the method `getInverse`
# which produces an object of type :class:`~openturns.InverseTrendTransform` that can be evaluated on a a field.
# For example, it may be useful in order to get the stationary field :math:`(\vect{x}^{stat}_0, \dots, \vect{x}^{stat}_{N-1})`
# and then analyze it with methods adapted to stationary processes (ARMA decomposition for example).
#

# %%
import openturns as ot


# %%
# Define a bi dimensional mesh
myIndices = [40, 20]
myMesher = ot.IntervalMesher(myIndices)
lowerBound = [0.0, 0.0]
upperBound = [2.0, 1.0]
myInterval = ot.Interval(lowerBound, upperBound)
myMesh = myMesher.build(myInterval)

# Define a scalar temporal Normal process on the mesh
# This process is stationary
amplitude = [1.0]
scale = [0.01] * 2
myCovModel = ot.ExponentialModel(scale, amplitude)
myXProcess = ot.GaussianProcess(myCovModel, myMesh)

# Create a trend function
# fTrend : R^2 --> R
#          (t,s) --> 1+2t+2s
fTrend = ot.SymbolicFunction(["t", "s"], ["1+2*t+2*s"])
fTemp = ot.TrendTransform(fTrend, myMesh)

# Add the trend to the initial process
myYProcess = ot.CompositeProcess(fTemp, myXProcess)

# Get a field from `myYtProcess`
myYField = myYProcess.getRealization()

# %%
# CASE 1 : we estimate the trend from the field

# Define the regression stategy using the `LARS` method
myBasisSequenceFactory = ot.LARS()

# Define the fitting algorithm using the
# `Corrected Leave One Out` or `KFold` algorithms
myFittingAlgorithm = ot.CorrectedLeaveOneOut()
myFittingAlgorithm_2 = ot.KFold()

# Define the basis function
# For example composed of 5 functions
myFunctionBasis = list(
    map(
        lambda fst: ot.SymbolicFunction(["t", "s"], [fst]),
        ["1", "t", "s", "t^2", "s^2"],
    )
)

# Define the trend function factory algorithm
myTrendFactory = ot.TrendFactory(myBasisSequenceFactory, myFittingAlgorithm)

# Create the trend transformation  of type `TrendTransform`
myTrendTransform = myTrendFactory.build(myYField, ot.Basis(myFunctionBasis))

# Check the estimated trend function
print("Trend function = ", myTrendTransform)

# %%
# CASE 2 : we impose the trend (or its inverse)

# The function g computes the trend : R^2 -> R
# g :      R^2 --> R
#          (t,s) --> 1+2t+2s
g = ot.SymbolicFunction(["t", "s"], ["1+2*t+2*s"])
gTemp = ot.TrendTransform(g, myMesh)

# Get the inverse trend transformation
# from the trend transform already defined
myInverseTrendTransform = myTrendTransform.getInverse()
print("Inverse trend function = ", myInverseTrendTransform)

# Sometimes it is more useful to define
# the opposite trend h : R^2 -> R
# in fact h = -g
h = ot.SymbolicFunction(["t", "s"], ["-(1+2*t+2*s)"])
myInverseTrendTransform_2 = ot.InverseTrendTransform(h, myMesh)

################################
# Remove the trend from the field `myYField`,
# `myXField = myYField - f(t,s)`
myXField2 = myTrendTransform.getInverse()(myYField)
# or from the class InverseTrendTransform
myXField3 = myInverseTrendTransform(myYField)

# Add the trend to the field `myXField2`,
# `myYField = f(t,s) + myXField2`
myInitialYField = myTrendTransform(myXField2)

# Get the trend function `f(t,s)`
myEvaluation_f = myTrendTransform.getTrendFunction()

# Evaluate the trend function `f` at a particular vertex
# which is the lower corner of the mesh
myMesh = myYField.getMesh()
vertices = myMesh.getVertices()
vertex = vertices.getMin()
trend_t = myEvaluation_f(vertex)
