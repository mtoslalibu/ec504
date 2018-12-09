""" Insert visualization """

import numpy as np
import matplotlib.pyplot as plt

with open('stat.txt') as f:
    lines = f.readlines()

ins_8 = []
ins_16 = []

for l in range(len(lines)):
    if ('XFastTrie(8) insert' in lines[l]):
        ins_8 = [float(n) for n in lines[l + 1].split(' ')[:-1]]
    elif ('XFastTrie(16) insert' in lines[l]):
        ins_16 = [float(n) for n in lines[l + 1].split(' ')[:-1]]

plt.plot(ins_8)
plt.plot(ins_16[:len(ins_8)])
plt.ylabel('Execution time (s)');
plt.legend(['XFastTrie(8) insert', 'XFastTrie(16) insert'])
plt.show()
