from snapylib import snafacade
from snapylib.communities import communities as communities
import networkx as nx  
import pylab as plt
import matplotlib.colors as mcolors
import networkx as nx
import networkx.algorithms.community as nx_comm

def louvaincommunities(G):
    """
    Find the best partition of a graph using the Louvain Community Detection Algorithm
    Returns: a listof sets (partition of G). Each set represents one community and contains all the nodes that constitute it.
    """
    comunidades = nx_comm.louvain_communities(
                G          = G,
                weight     = 'weight',
                resolution = 0.0000000001
             )
    return comunidades

G = snafacade.loadGraphml("graph.graphml")
#louvain algorithm
partition1 = louvaincommunities(G)
comunidades_map = {}
print(partition1)
for i in range(len(partition1)):
    comunidades_map.update(dict.fromkeys(partition1[i], i))

comunidades_map
color_pallet = list(mcolors.XKCD_COLORS.values())
color_nodos = []
for node in G:
    color_nodos.append(color_pallet[comunidades_map[node]])
fig, ax = plt.subplots(figsize=(6, 4))
nx.draw(G, node_color=color_nodos, with_labels=False, ax=ax)
plt.savefig('louvainECG.png')