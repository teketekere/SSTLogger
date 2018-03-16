import numpy as np
import pickle
from sst import SST


def zscore(x, axis=None):
    xmean = x.mean(axis=axis, keepdims=True)
    xstd = np.std(x, axis=axis, keepdims=True)
    zscore = (x - xmean) / xstd
    return zscore


# read data
'''
with open('trainData.pickle', 'rb') as f:
    data = pickle.load(f).astype(float)
x = zscore(data)
'''
x = np.arange(0, 10, 0.01)
x = [(d / 2.0) + np.sin(2.0 * np.pi * d) + np.random.normal(0, 0.1) if (d < 6 or d > 7) else (d / 2.0) + np.sin(23.7 * np.pi * d) + np.random.normal(0, 1) for d in x]
x = np.array([x]).T
x = zscore(x)
print(x.shape)

interval = 1
maxLen = x.shape[0]
iterNum = maxLen // interval

# calc score
sst = SST(width=20)
for iter in range(iterNum):
    data = x[interval * iter: interval * (iter + 1)]
    sst.updateData(*(data.T))
sst.debugView()
