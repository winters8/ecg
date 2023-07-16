import pandas as pd
import matplotlib.pyplot as plt
from scipy.signal import find_peaks


# Leer el archivo CSV con los datos del ECG
df = pd.read_csv('MUSE_20180111_160439_59000.csv')

# Obtener las columnas correspondientes a los valores de tiempo y voltaje
tiempo = df['tiempo']
voltaje = df['voltaje']

# Crear el gráfico del ECG
plt.plot(tiempo, voltaje)
plt.xlabel('Tiempo')
plt.ylabel('Voltaje')
plt.title('Electrocardiograma')
plt.grid(True)

# Mostrar el gráfico
plt.show()
plt.savefig('matplot2.png')

# Detectar picos en el ECG
picos, _ = find_peaks(voltaje, height=0)

# Calcular el número de picos por minuto
tiempo_total = tiempo.iloc[-1] - tiempo.iloc[0]  # Duración total del ECG
minutos = tiempo_total / 60
pulsaciones_por_minuto = len(picos) / minutos

print('Pulsaciones por minuto:', pulsaciones_por_minuto)