import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Hier einfach die Messwertdatei auswählen
value = 'innen'
path = value + '.csv'
plot = value + 'Plt2.svg'
df = pd.read_csv(
    path,
    names=["time", "PM1", "PM2,5", "PM4", "PM10", "Typical", "Bucket0,3-1",
           "Bucket1-2,5", "Bucket2,5-4", "Bucket4-10"],
    skiprows=1)
df.time = (df.time - df.time[0]) / 1000
df.set_index('time')

# bei y = die nicht zu plottenden Werte raus nehmen
fig, ax1 = plt.subplots(figsize=(12, 8))

df.plot(x='time',
        y=["Bucket0,3-1",
           "Bucket1-2,5", "Bucket2,5-4", "Bucket4-10"],
        ax=ax1)
plt.title('Feinstaubkonzentration im Innenraum', fontsize="24")
plt.xlabel('Zeit [s]', fontsize="20")
plt.ylabel('Feinstaubkonzentration [µg/m^3]',
           fontsize="20")
plt.xticks(fontsize="14")
plt.yticks(fontsize="14")
plt.legend(fontsize="20", loc='best')  # Display legend

plt.tight_layout()

# ax2 = ax1.twinx()
# ax2.bar(df['time'], df['erdbeben'], color='yellow', alpha=0.03,
#        label='Erdbeben')
# manager = plt.get_current_fig_manager()
# manager.resize(*manager.window.maxsize())
plt.savefig(plot)
plt.show()
# plt.savefig(plot)
