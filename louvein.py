from snapylib import snafacade
from snapylib.communities import communities as communities
import networkx as nx  
import pylab as plt
import matplotlib.colors as mcolors
import networkx as nx
import networkx.algorithms.community as nx_comm
import community as community_louvain
import matplotlib.cm as cm
import os
import csv
import io
import json
import re
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

G = snafacade.loadGraphml("graphgiant.graphml")
#louvain algorithm
partition = community_louvain.best_partition(G)
file=(".\csv\dataecgs.csv")
List1=[]
list2=[]
list3=[]
media1=0
media2=0
media3=0

for nombre, valor in partition.items():
        if valor==0:
            List1.append(nombre)
        else:
            if valor==1:
                    list2.append(nombre)
            else:
                    list3.append(nombre)

def recogervalor(nombre):
    with open (file,'r') as csvfile:
        reader = csv.reader(csvfile)
        header_row = next(reader)
        column_index = header_row.index('node')
        column_index1 = header_row.index('measures')
        valor=0
        for row in reader:
            name= row[column_index]
            data = row[column_index1]
            i=0
            if nombre == name:
                print("iguales¡¡")
                p = re.compile('(?<!\\\\)\'')
                data = p.sub('\"', data)
                data_like_objetc = io.StringIO(data)
                data= json.load(data_like_objetc)
                valor=data["bpm"]
                break
            else:
                 continue
        return(valor)
                         

for nombre in List1:
    print (f"nombre a comprobar:{nombre}")
    media1=media1+recogervalor(nombre)
media1=media1/len(List1)
for nombre in list2:
    print (f"nombre a comprobar:{nombre}")
    media2=media2+recogervalor(nombre)
media2=media2/len(list2)
for nombre in list3:
    print (f"nombre a comprobar:{nombre}")
    media3=media3+recogervalor(nombre)
media3=media3/len(list3)
print (f"la media1 es:{media1}\n la media2 es:{media2}\n la media3 es: {media3}")

                           
"""
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
"""
# draw the graph
fig = plt.figure(figsize=(50, 50), dpi=200)
pos = nx.spring_layout(G)
# color the nodes according to their partition
cmap = cm.get_cmap('viridis', max(partition.values()) + 1)
nx.draw_networkx_nodes(G, pos, partition.keys(), node_size=40,
cmap=cmap, node_color=list(partition.values()))
nx.draw_networkx_edges(G, pos, alpha=0.5)
plt.savefig('louvainECG.png')