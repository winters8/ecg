import pandas as pd
import matplotlib.pyplot as plt
import ecg_plot
import numpy as np
plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

df = pd.read_csv('prueba1.csv')
# Get the sampling rate from the CSV file (assuming it's in the header row)
sampling_rate = float(df.columns[1].split()[0])

# Calculate the duration of the ECG signal
duration = len(df) / sampling_rate

# Create a time axis starting from 0 with a step size of 1/sampling_rate
time = np.arange(0, duration, 1/sampling_rate)

# Get the voltage values for all 12 leads from the DataFrame
lead_names = ['I', 'II', 'III', 'aVR', 'aVL', 'aVF', 'V1', 'V2', 'V3', 'V4', 'V5', 'V6']
leads = [df[lead_name] for lead_name in lead_names]
print (leads)
# Plot the ECG signal for all 12 leads
fig, axs = plt.subplots(6, 2, figsize=(12, 16), sharex=True, sharey=True)
for i, ax in enumerate(axs.flatten()):
    ax.plot(time, leads[i])
    ax.set_title(lead_names[i])
plt.xlabel('Time (s)')
plt.ylabel('Voltage (mV)')
plt.suptitle('12-Lead ECG Signal')
plt.show()