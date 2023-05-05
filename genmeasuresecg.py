import os
import csv
import pandas as pd
import matplotlib.pyplot as plt
import heartpy as hp
import multiprocessing
import time
class node:
    def __init__ (self,file,measure):
        self.file=file
        self.measures=measure

def processfile(file):
    try:
        signal = hp.get_data(file, delim =',', column_name = 'II')
        working_data, measures = hp.process(signal, 500.0)
    except:
        measures= 0
    return file,measures

def multiproceso():
    if __name__ =='__main__':
        dir_path= "D:/Descargas/ECGDataDenoised"
        file_list = os.listdir(dir_path)
        files = [os.path.join(dir_path, f) for f in os.listdir(dir_path) if os.path.isfile(os.path.join(dir_path, f))]
        manager = multiprocessing.Manager()
        result_list = manager.list()
        listnodes=[]
        with multiprocessing.Pool() as pool:
            for file,result in pool.imap_unordered(processfile, files):
                node1=node(file,result)
                result_list.append(node1)
            pool.close()
            pool.join()
        print ("All proceses are done")
        with open('dataecgs.csv', 'w', newline='') as file:
            writer = csv.writer(file)
            # Write the header row
            writer.writerow(['node', 'measures'])
            #Write each nodes as a row in the CSV file
            for node1 in result_list:
               writer.writerow([node1.file, node1.measures])
               
multiproceso()