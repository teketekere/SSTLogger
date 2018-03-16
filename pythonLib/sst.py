import matplotlib.pyplot as plt
import numpy as np
# from scipy.sparse import csc_matrix
# from scipy.sparse.linalg import svds
from scipy import linalg


class SST(object):
    '''
    パラメータの意味は「異常検知と変化検知 p122を参照」
    updateData()で逐次的にデータを更新→変化度を計算
    @param width: widtch of test and trajectory matrices
    @param n: row band of trajectory matrix
    @param k: row band of test matrix
    @param lag: lag time
    @param r: patter number(= svd vector number) of trajectory matrix
    @param m: patter number(= svd vector number) of test matrix
    @param data: time series data. must be 1-dimensional ndarray
    @param score: variability of self.data(\in [0, 1]. 0:normal, 1:abnormal)
    '''
    def __init__(self, width):
        self.width = width
        self.n = self.width // 2
        self.k = self.width // 2
        self.lag = self.k // 2
        self.r = 3
        self.m = 2
        self.minlength = self.lag + self.n + self.width - 1
        self.data = np.array([])
        self.score = np.array([])

    def updateData(self, data):
        # todo: add check data size
        self.data = np.append(self.data, data)
        dummyScore = np.zeros_like(data)
        dummyScore[-1] = self.calcNewestScore()
        self.score = np.append(self.score, dummyScore)

    def calcNewestScore(self):
        # check data length is
        if(self.minlength > len(self.data)):
            return 0
        # calc variability(= score)
        X = self.getTrajectoryMatrix()
        Z = self.getTestMatrix()
        return self.calcScore(X, Z)

    def calcScore(self, X, Z):
        # U, _, _ = svds(X, k=2, return_singular_vectors="u")
        Ux, _, _ = linalg.svd(X, full_matrices=False)
        print(Ux.shape)
        Ux = Ux[:, :self.r]
        Uz, _, _ = linalg.svd(Z, full_matrices=False)
        Uz = Uz[:, :self.m]
        P = np.transpose(Ux) @ Uz
        score = 1 - linalg.norm(P, ord=2)
        return score

    def getTrajectoryMatrix(self):
        # pandas.rolling()を使ったほうがいい？？
        X = [[self.data[-1 - self.lag - self.n - self.width + 2 + i + j] for i in range(self.width)] for j in range(self.n)]
        # return csc_matrix(X, dtype=float)
        return np.transpose(np.array(X))

    def getTestMatrix(self):
        # pandas.rolling()を使ったほうがいい？？
        Z = [[self.data[-1 - self.k - self.width + 2 + i + j] for i in range(self.width)] for j in range(self.k)]
        # return csc_matrix(Z, dtype=float)
        return np.transpose(np.array(Z))

    def debugView(self):
        print(max(self.score))
        print(min(self.score))
        plt.subplot(2, 1, 1)
        plt.plot(self.data)
        plt.subplot(2, 1, 2)
        plt.plot(self.score)
        plt.show()
