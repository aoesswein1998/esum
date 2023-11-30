import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Hier einfach die Messwertdatei auswählen
values = ['Tischwackeln']
for value in values:
    path = value + '.csv'
    plot = value + 'rpmPlt.png'
    data1 = pd.read_csv(
        path, names=["SI", "PGA", "x", "y", "z", "time", "erdbeben"],
        skiprows=1)
    x = data1.x * 4 / 16383
    y = data1.y * 4 / 16383
    z = data1.z * 4 / 16383
    acc = np.sqrt(x ** 2 + y ** 2 + z ** 2)
    SI = data1.SI
    PGA = data1.PGA
    time = (data1.time - data1.time[0]) / 1000
    erdbeben = data1.erdbeben
    data = {'SI': SI, 'PGA': PGA, 'x': x, 'y': y, 'z': z, 'time': time,
            'acc': acc,
            'erdbeben': erdbeben}
    df = pd.DataFrame(data)
    df.set_index('time')

    # bei y = die nicht zu plottenden Werte raus nehmen
    ax1 = df.plot(x='time', y=['acc', 'SI', 'PGA'],
                  color=['green', 'red', 'blue'])
    plt.title('Wackeln am Tisch', fontsize="24")
    plt.xlabel('Zeit / s', fontsize="20")
    plt.ylabel('Beschleunigung / m/s^2 // Grundgeschwindigkeit / m/s',
               fontsize="20")
    plt.xticks(fontsize="14")
    plt.yticks(fontsize="14")
    plt.legend(fontsize="20", loc='best')  # Display legend

    ax2 = ax1.twinx()
    ax2.bar(df['time'], df['erdbeben'], color='yellow', alpha=0.03,
            label='Erdbeben')
    #manager = plt.get_current_fig_manager()
    #manager.resize(*manager.window.maxsize())
    plt.show()
    #plt.savefig(plot)
