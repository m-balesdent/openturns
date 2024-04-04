import openturns as ot
from matplotlib import pyplot as plt
from openturns.viewer import View

distribution = ot.BayesDistribution()

distribution.setDescription(["$Y$", "$X$"])
pdf_graph = distribution.drawPDF()
pdf_graph.setTitle(str(distribution))
fig = plt.figure(figsize=(10, 5))
pdf_axis = fig.add_subplot(111)
View(pdf_graph, figure=fig, axes=[pdf_axis], add_legend=False)
