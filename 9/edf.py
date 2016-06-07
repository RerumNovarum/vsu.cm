import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys

if __name__ == '__main__':
    s = pd.concat([pd.Series.from_csv(f) for f in sys.argv[1:]])
    s.hist(cumulative=True, normed=True, bins=len(s))
    plt.show()
