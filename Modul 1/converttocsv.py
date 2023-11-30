import pandas as pd
import numpy as np

Dateien = ['05Hz.csv', '1Hz.csv', '15Hz.csv', '2Hz.csv', '25Hz.csv', '3Hz.csv',
           '35Hz.csv', '4Hz.csv', '45Hz.csv', '5Hz.csv', '6Hz.csv',
           '7Hz.csv', '50rpm.csv', '100rpm.csv', '150rpm.csv', '200rpm.csv',
           '250rpm.csv', '300rpm.csv', '350rpm.csv', '400rpm.csv',
           '420rpm.csv', 'Espresso.csv', 'Tischwackeln.csv']
# Lade die CSV-Datei in ein Pandas DataFrame
for file_path in Dateien:
    df = pd.read_csv(file_path, names=['si', 'pga', 'x', 'y', 'z', 'time'],
                     dtype=object)

    # Erstelle eine neue Spalte mit dem Namen 'Neue_Spalte'
    # Die neue Spalte enthält '0', wenn die Spalte 'Alte_Spalte' den Wert 0 hat, ansonsten '1'
    df['erdbeben'] = df['si'].apply(lambda x: '0' if x == '0' else '1')

    # Speichere das aktualisierte DataFrame in eine neue CSV-Datei
    neue_datei_path = file_path
    df.to_csv(neue_datei_path, index=False)

    print(f'Die neue Datei wurde erstellt: {neue_datei_path}')
