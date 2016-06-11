#!/usr/bin/python3

import os
import sys

k = 4
if __name__ == '__main__':
    N = int(sys.argv[1])
    for n in range(2, N+1):
        os.system("./stats %d %d > degree.%d.sample"%(n,k,n))
