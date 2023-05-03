import os
import csv
import pandas as pd
import matplotlib.pyplot as plt
import heartpy as hp
class node:
    def __init__ (self,node,measure):
        self.node=node
        self.measures=measure
listnodes = []
dir_path= "C:/Users/plati/Downloads/ECGDataDenoised"
file_list = os.listdir(dir_path)
for file_name in file_list:
    print(file_name)
    # Resample the signal to 100 Hz
    try:
        signal = hp.get_data(os.path.join(dir_path, file_name), delim =',', column_name = 'II')
        working_data, measures = hp.process(signal, 500.0)
    except:
        print("Error archivo")  
    nodeappend = node(file_name,measures)
    listnodes.append(nodeappend)
print (listnodes)
with open('dataecgs.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    # Write the header row
    writer.writerow(['node', 'measures'])

    # Write each person as a row in the CSV file
    for node1 in listnodes:
        writer.writerow([node1.node, node1.measures])