import pandas as pd
import matplotlib.pyplot as plt
import ecg_plot
import numpy as np
plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

headers = ['I','II','III','aVR','aVL','aVF','V1','V2','V3','V4','V5','V6']

df = pd.read_csv('prueba1.csv')
specific_colum =df["II"]
fs=500
time_data = np.arange(specific_colum.size) / fs
plt.plot(time_data,specific_colum)
plt.xlabel("time in s")
plt.ylabel("ECG in mV")
plt.show()