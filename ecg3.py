import pandas as pd
import matplotlib.pyplot as plt
import heartpy as hp
import time
# Resample the signal to 100 Hz
signal = hp.get_data('prueba2.csv', delim =',', column_name = 'II')
working_data, measures = hp.process(signal, 500.0)
plot_object = hp.plotter(working_data, measures,title='Heart Beat Detection on Noisy Signal',show=False)
plot_object.savefig('plot_1.jpg')
