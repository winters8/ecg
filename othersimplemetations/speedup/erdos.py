import networkx as nx
import csv
import random

 

G= nx.erdos_renyi_graph(1000,0.003)

 

for (u,v,w) in G.edges(data=True):

    w['weight'] = random.random()
csv_file='erdos100.csv'
with open(csv_file, 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Source', 'Target', 'Weight'])  # Write header row
    
    for (u, v, attr) in G.edges.data():
        writer.writerow([u, v, attr['weight']])
        
print(f"CSV file '{csv_file}' created successfully.")