import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data1 = pd.read_csv(
    r'putty.csv', names=["x", "y", "z"])

length1 = int(len(data1.x)/2)
length2 = int(len(data1.y)/2)
length3 = int(len(data1.z)/2)
x = data1.x.iloc[:length1]
y = data1.y.iloc[:length2]
z = data1.z.iloc[:length3]
#plt.plot(list, x, label='x')
#plt.plot(list, y, label='y')
#plt.plot(list, z, label='z')
plt.hist(x, histtype=u'step', density=True, label='x')
plt.hist(y, histtype=u'step', density=True, label='y')
plt.hist(z, histtype=u'step', density=True, label='z')
plt.legend()
plt.show()
