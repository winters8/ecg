from snapylib import snafacade
from snapylib.topological import indexes as tindexes
from snapylib.centralities import indexes as cindexes
from snapylib.communities import communities as communities
import matplotlib.colors as mcolors
import networkx as nx
import networkx.algorithms.community as nx_comm
G = snafacade.loadGraphml("graphgiant.graphml")
print( "##################################################\n#############Topological network indexes##########\n##################################################")
N = tindexes.numNodes(G)
print("Number of nodes (N): ", N)
L = tindexes.numEdges(G)
print("Number of edges/links (L): ", L)
avgK = tindexes.averageDegree(G)
print("Average degree <k>: ", avgK)
ro = tindexes.density(G)
print("Density (ro): ", ro) #how sparce the graph/network is: L/Lmax
lmax = tindexes.diameter(G)
print("Diameter (lmax): ", lmax) 
radius = tindexes.radius(G)
print("Radius: ", radius)
import networkx as nx  
import numpy as np 
import pylab as plt # This module depens on Numpy and Matplotlib

# Set up sublot/canvas array e.j.: subplot(nrows, ncols, index)
# and indicate the current index
fig = plt.figure(figsize=(50,50),dpi=200)
plt.title("Original ECG PADGM graph")
# Draw the original graph
pos1 = nx.fruchterman_reingold_layout(G)
nx.draw(G,pos=pos1,with_labels=False,edge_color='black', width=1.0)
plt.savefig('matplot.png')
plt.clf()

plt.title("Colored and resized nodes (e.g. Eigenvector centrality) - ECG PADGM graph")
d = cindexes.eigenvectorCentrality(G,tol=1e-06) # Change by any other centrality index you want...
# d = cindexes.betweennessCentrality(G) # Change by any other centrality index you want...
n_color = np.asarray(list(d.values()))
nx.draw(G, pos=pos1,nodelist=d.keys(), node_color=n_color,edge_color='black', width=1.0, node_size=[(v*5000)+50 for v in d.values()], with_labels=False)
# Finally make the array plot (and their content) visible
plt.savefig('matplot2.png')
