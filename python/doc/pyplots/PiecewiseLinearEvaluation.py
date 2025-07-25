import openturns as ot
from openturns.viewer import View

locations = ot.RegularGrid(0.0, 0.25, 11).getVertices().asPoint()
f = ot.SymbolicFunction(["x"], ["sin(pi_*x)"])
values = f(ot.Sample.BuildFromPoint(locations))
func_P1 = ot.PiecewiseLinearEvaluation(locations, values)

graph = ot.Graph(
    r"Piecewise linear interpolation of $x  \mapsto \sin(\pi x)$", r"$x$", r"$y$", True
)
cloud = ot.Cloud(ot.Sample.BuildFromPoint(locations), values)
cloud.setPointStyle("square")
graph.add(cloud)
draw_f = f.draw(-0.5, 3.0, 1024).getDrawable(0)
draw_f.setLineStyle("dashed")
graph.add(draw_f)
graph.add(func_P1.draw(-0.5, 3.0, 1024).getDrawable(0))
graph.setColors(["lightblue", "blue", "red"])

view = View(graph, figure_kw={"figsize": (10, 4)}, add_legend=False)
