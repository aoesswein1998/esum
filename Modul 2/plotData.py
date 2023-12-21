import pandas as pd
import numpy as np
from matplotlib import pyplot as plt

PM2p5A = pd.read_csv("PM2,5_draußenRauchen2-20231221-1019.csv", index_col=3, parse_dates=True)
PM1p0A = pd.read_csv("PM1_draußenRauchen2-20231221-1357.csv", index_col=3, parse_dates=True)
PM2p5I = pd.read_csv("PM2,5_drinnenRauchen-20231220-1224.csv", index_col=3, parse_dates=True)
PM1p0I = pd.read_csv("PM1_drinnenRauchen-20231220-2107.csv", index_col=3, parse_dates=True)
fig, ax1 = plt.subplots(figsize=(12, 8))


plt.title("Feinstaubkonzentration beim Rauchen im Innenraum", fontsize=26)
#PM1p0A["value"].plot(label='PM1 Außen', ax=ax1)
#PM2p5A["value"].plot(label='PM2,5 Außen', ax=ax1)
PM1p0I["value"].plot(label='PM1 Innen', ax=ax1)
PM2p5I["value"].plot(label='PM2,5 Innen', ax=ax1)
plt.ylabel("Konzentration in \u03bcg/m^3", fontsize=26)
plt.xlabel("Tag und Uhrzeit", fontsize=26)
plt.legend(fontsize="20")
plt.xticks(fontsize="14")
plt.yticks(fontsize="14")

plt.tight_layout()
plt.savefig('innenrauchen.svg')
plt.show()
