import pandas as pd
import numpy as np
from matplotlib import pyplot as plt

df = pd.read_csv("PM2,5_drinnenRauchen-20231220-1224.csv", index_col=3, parse_dates=True)

plt.ylabel("Steffi ist die beste")
df["value"].plot()


plt.show() 