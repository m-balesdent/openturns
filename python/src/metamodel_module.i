// SWIG file metamodel_module.i

%module(package="openturns", docstring="Meta-modelling.") metamodel
#pragma SWIG nowarn=302,509

%{
#include "openturns/OTconfig.hxx"
#include "openturns/OTBase.hxx"
#include "openturns/OTModel.hxx"
#include "openturns/OTDistribution.hxx"
#include "openturns/OTWeightedExperiments.hxx"
#include "openturns/OTOrthogonalBasis.hxx"
#include "openturns/OTMetaModel.hxx"
%}

%include typemaps.i
%include OTtypes.i
%include OTexceptions.i
%include std_vector.i

%include BaseTypCollection.i
%include BaseFuncCollection.i
%import base_module.i

/* Uncertainty/Model */
/* Uncertainty/Distribution */
%import model_copula_module.i
%import UncertaintyModelCopulaTemplateDefs.i
// KrigingResult::operator() returns Normal
%import Normal.i

/* Uncertainty/Algorithm/WeightedExperiment */
%import weightedexperiment_module.i

/* Uncertainty/Algorithm/OrthogonalBasis */
%import orthogonalbasis_module.i
%import UncertaintyOrthogonalBasisTemplateDefs.i

/* Uncertainty/Model */
%import randomvector_module.i

/* Uncertainty/Algorithm/Metamodel */
%include MetaModelResult.i
%include KrigingResult.i
%include LinearModelResult.i
%include MetaModelAlgorithm.i
%include LinearTaylor.i
%include QuadraticTaylor.i
%include LinearLeastSquares.i
%include QuadraticLeastSquares.i
%include AdaptiveStrategyImplementation.i
%include FixedStrategy.i
%include CleaningStrategy.i
%include AdaptiveStrategy.i
%include ProjectionStrategyImplementation.i
%include LeastSquaresStrategy.i
%include IntegrationStrategy.i
%include ProjectionStrategy.i
%include FunctionalChaosResult.i
%include FunctionalChaosAlgorithm.i
%include FunctionalChaosSobolIndices.i
%include MetaModelValidation.i
%include GeneralLinearModelResult.i
%include GeneralLinearModelAlgorithm.i
%include KrigingAlgorithm.i
%include LinearModelStepwiseAlgorithm.i
%include LinearModelAlgorithm.i
%include LinearModelAnalysis.i

/* Uncertainty/Model */
%include RandomVector.i
%include CompositeRandomVector.i
%include ThresholdEvent.i
%include DomainEvent.i
%include ProcessEvent.i
%include DeconditionedRandomVector.i
%include StandardEvent.i
%include IntersectionEvent.i
%include UnionEvent.i

/* Uncertainty/Algorithm/Metamodel */
%include FunctionalChaosRandomVector.i
%include FunctionalChaosValidation.i
%include KrigingRandomVector.i
%include LeastSquaresExpansion.i
%include IntegrationExpansion.i
%include FieldFunctionalChaosResult.i
%include FieldToPointFunctionalChaosAlgorithm.i
%include FieldFunctionalChaosSobolIndices.i
%include PointToFieldFunctionalChaosAlgorithm.i

/* At last we include template definitions */
%include UncertaintyMetaModelTemplateDefs.i
