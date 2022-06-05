import matplotlib.pyplot as plt
import numpy as np

x = []
y = []
z = []

qsortfile = open("qsort_time.txt", 'r')
prunefile = open("prune_time.txt", 'r')
for data in prunefile:
    data.strip('\n')
    x.append(float(data))

for num in qsortfile:
    data.strip('\n')
    y.append(float(num))

for i in range(10000000, 31000000, 1000000):
    z.append(i)

plt.scatter(z, x, s = 4, c = "red")
plt.scatter(z, y,s= 4, c = "blue")
plt.title('[109070024] Average Running Time')
plt.xlabel('Problem Size n')
plt.ylabel('time(sec)')
plt.legend(["Prune & Search", "Qsort"], loc = 0)
plt.grid()

plt.show()