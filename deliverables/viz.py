"""Visualization script"""

import numpy as np
import matplotlib.pyplot as plt

class Stat:
    def __init__(self, ds, ins, lookup, pred, suc, dele):
        self.ds = ds
        self.ins = ins
        self.lookup = lookup
        self.pred = pred
        self.suc = suc
        self.dele = dele

stats = []
lines = []

with open('stat.txt', 'r') as f:
    lines = f.readlines()

# fill the data
for offset in range(0, len(lines), 10):
    stats.append(Stat(lines[offset].split(' ')[0],
                  [float(n) for n in lines[offset + 1].split(' ')[:-1]],
                  [float(n) for n in lines[offset + 3].split(' ')[:-1]],
                  [float(n) for n in lines[offset + 5].split(' ')[:-1]],
                  [float(n) for n in lines[offset + 7].split(' ')[:-1]],
                  [float(n) for n in lines[offset + 9].split(' ')[:-1]]))

# prepare the data
dss = [s.ds for s in stats]
avg_ins = [sum(s.ins) / float(len(s.ins)) * 10**3 for s in stats]
avg_lookup = [sum(s.lookup) / float(len(s.lookup)) * 10**3 for s in stats]
avg_pred = [sum(s.pred) / float(len(s.pred)) * 10**3 for s in stats]
avg_suc = [sum(s.suc) / float(len(s.suc)) * 10**3 for s in stats]
avg_dele = [sum(s.dele) / float(len(s.dele)) * 10**3 for s in stats]

#  visualize
n_groups = len(stats)
fig, ax = plt.subplots()
index = np.arange(n_groups)
bar_width = 0.2

plt.bar(index, avg_ins, bar_width, color='g',
        label='Insert')
plt.bar(index + bar_width, avg_lookup, bar_width, color='r',
        label='Lookup')
plt.bar(index + 2*bar_width, avg_pred, bar_width, color='b',
        label='getPredecessor')
plt.bar(index + 3*bar_width, avg_suc, bar_width, color='y',
        label='getSuccessor')
plt.bar(index + 4*bar_width, avg_dele, bar_width, color='c',
        label='Delete')

plt.ylabel('Execution time (ms)');
plt.title('VEB Tree vs x-Fast tree basic operations')
plt.xticks(index + 2*bar_width, dss)
plt.legend()

plt.tight_layout()
plt.show()
