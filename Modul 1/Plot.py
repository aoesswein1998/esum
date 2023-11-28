import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data1 = pd.read_csv(
    r'Espresso.csv', names=["SI","PGA","x", "y", "z"])

length1 = int(len(data1.x)/2)
list1 = [i for i in range(length1)]
length2 = int(len(data1.y)/2)
list2 = [i for i in range(length2)]
length3 = int(len(data1.z)/2)
list3 = [i for i in range(length3)]
x = data1.x.iloc[:length1]*4/16383
y = data1.y.iloc[:length2]*4/16383
z = data1.z.iloc[:length3]*4/16383
SI = data1.SI
PGA = data1.PGA
#data = {'x':x, 'y':y, 'z':z}
data = {'SI':SI, 'PGA':PGA}
df = pd.DataFrame(data)

df.plot(style='o-', markersize=6, title='Betrieb einer Espressomaschine')

plt.xlabel('Sample number')
plt.ylabel('Beschleunigung / [m/s^2] // Grundgeschwindigkeit / [m/s]')

plt.legend(loc='best')  # Display legend
plt.show()
#plt.plot(x, list1, label='x')
#plt.hist(x, histtype=u'step', density=True, label='x')
#plt.hist(y, histtype=u'step', density=True, label='y')
#plt.hist(z, histtype=u'step', density=True, label='z')
#plt.xlabel("Messwert Nr")
#plt.ylabel("Beschleunigung /[m/s^2]")
#plt.legend()
#plt.show()
