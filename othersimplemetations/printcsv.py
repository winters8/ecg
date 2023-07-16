import pandas as pd
import matplotlib.pyplot as plt


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

intervalos_tiempo = tiempo.diff().dropna()
promedio_intervalo_tiempo = intervalos_tiempo.mean()
# Convierte el promedio de intervalo de tiempo a pulsaciones por minuto
pulsaciones_por_minuto = 60 / promedio_intervalo_tiempo
print("Pulsaciones por minuto:", pulsaciones_por_minuto)