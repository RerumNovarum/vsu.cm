#!/usr/bin/python3
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys
import re
import traceback

if __name__ == '__main__':
    d = dict()
    delim = re.compile(r',|;|\s|\n')
    maxn = 0
    for fname in sys.argv[1:]:
        try:
            with open(fname, mode='r', encoding='utf8') as f:
                s = pd.Series(float(x) for x in delim.split(f.read()) if x)
        except:
            print('failed while reading "%s"'%f)
            traceback.print_exc()
            exit(0)
        dsq = sum(s**2)
        n = len(s)
        maxn = max(n,maxn)
        if n in d: d[n].append(dsq)
        else: d[n] = {n: dsq}
    nn = sorted(d.keys())
    means = pd.Series([np.sqrt(sum(d[n]))/len(d[n]) for n in nn])
    plt.plot(nn, means)
    plt.show()

