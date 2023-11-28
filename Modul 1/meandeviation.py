import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data1 = pd.read_csv(
    r'2g.csv', names=["x", "y", "z"])
data2 = pd.read_csv(
    r'4g.csv', names=["x", "y", "z"])
data3 = pd.read_csv(
    r'8g.csv', names=["x", "y", "z"])

length1 = int(len(data1.x)/2)
length2 = int(len(data1.y)/2)
length3 = int(len(data1.z)/2)
x1 = data1.x.iloc[:length1]
y1 = data1.y.iloc[:length2]
z1 = data1.z.iloc[:length3]

length1 = int(len(data2.x)/2)
length2 = int(len(data2.y)/2)
length3 = int(len(data2.z)/2)
x2 = data2.x.iloc[:length1]
y2 = data2.y.iloc[:length2]
z2 = data2.z.iloc[:length3]

length1 = int(len(data3.x)/2)
length2 = int(len(data3.y)/2)
length3 = int(len(data3.z)/2)
x3 = data3.x.iloc[:length1]
y3 = data3.y.iloc[:length2]
z3 = data3.z.iloc[:length3]

print("2g:")
print(x1.mean())
print(x1.std())
print(y1.mean())
print(y1.std())
print(z1.mean())
print(z1.std())

print("4g:")
print(x2.mean())
print(x2.std())
print(y2.mean())
print(y2.std())
print(z2.mean())
print(z2.std())

print("8g:")
print(x3.mean())
print(x3.std())
print(y3.mean())
print(y3.std())
print(z3.mean())
print(z3.std())