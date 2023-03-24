import pandas as pd
import matplotlib.pyplot as plt
import ecg_plot

plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

headers = ['I','II','III','aVR','aVL','aVF','V1','V2','V3','V4','V5','V6']

df = pd.read_csv('prueba1.csv')

ecg_plot.plot(df, sample_rate=500, title = 'ECG')
ecg_plot.show()