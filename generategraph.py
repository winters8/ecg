import os
import csv
import pandas as pd
import heartpy as hp
import multiprocessing
import networkx as nx
import json
import re
import io
from joblib import parallel_backend,Parallel, delayed

G= nx.Graph()

def comprobarsemejanza(record1,record2):
    if abs(record1-record2<10):
        return True
     
def addnodes(file,G):
     with open (file,'r') as csvfile:
        reader = csv.reader(csvfile)
        header_row = next(reader)
        column_index = header_row.index('node')
        for row in reader:
            name= row[column_index]
            G.add_node(name)
        return G
     
def multiproceso(i,rows,header_row,G):
    pid = os.getpid()
    column_index = header_row.index('node')
    column_index1 = header_row.index('measures')
    try:
        for j in range(i+1, len(rows)):
            name1= rows[i][column_index]
            print(f"procesando {i} en {pid}")
            data1=rows[i][column_index1]
            p = re.compile('(?<!\\\\)\'')
            data1 = p.sub('\"', data1)
            data_like_objetc = io.StringIO(data1)
            data1= json.load(data_like_objetc)
            name2 = rows[j][column_index]
            data2=rows[j][column_index1]
            data2 = p.sub('\"', data2)
            data_like_objetc2 = io.StringIO(data2)
            data2= json.load(data_like_objetc2)
            if abs(data1["bpm"]-data2["bpm"])<10:
                G.add_edge(name1,name2)
    except json.decoder.JSONDecodeError as e:
        print (f"Error parsin JSIN data {e}")
    return G


def addedges(file,G):
    if __name__ == "__main__":
      with open (file,'r') as csvfile:
        reader = csv.reader(csvfile)
        reader = csv.reader(csvfile)
        header_row = next(reader)
        column_index = header_row.index('node')
        column_index1 = header_row.index('measures')
        rows = list(reader)
        G=Parallel(n_jobs=20)(delayed(multiproceso)(i,rows,header_row,G) for i in range(len(rows)))
    return G
            

def addedges2(file,G):     
    with open (file,'r') as csvfile:
        reader = csv.reader(csvfile)
        reader = csv.reader(csvfile)
        header_row = next(reader)
        column_index = header_row.index('node')
        column_index1 = header_row.index('measures')
        rows = list(reader)
        for i in range(len(rows)):
            try:
                for j in range(i+1, len(rows)):
                    try:
                        name1= rows[i][column_index]
                        data1=rows[i][column_index1]
                        p = re.compile('(?<!\\\\)\'')
                        data1 = p.sub('\"', data1)
                        data_like_objetc = io.StringIO(data1)
                        data1= json.load(data_like_objetc)
                        name2 = rows[j][column_index]
                        data2=rows[j][column_index1]
                        data2 = p.sub('\"', data2)
                        data_like_objetc2 = io.StringIO(data2)
                        data2= json.load(data_like_objetc2)
                        if comprobarsemejanza(data1["bpm"],data2["bpm"])==True:
                            G.add_edge(name1,name2)
                        print (len(rows)-i)
                    except json.decoder.JSONDecodeError as e:
                        print (f"Error parsin JSIN data {e}")
                        continue              
            except json.decoder.JSONDecodeError as e:
                print (f"Error parsin JSIN data {e}")
                continue               
        return G


G1=addedges("dataecgs.csv",G)
for edge in G1:
    G.add_edges_from(edge.edges)
G=addnodes("dataecgs.csv",G)
nx.write_graphml(G,"graph.graphml")
