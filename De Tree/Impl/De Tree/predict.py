"""
predict by de tree.
"""
import pickle
import de_tree
import numpy as np
with open('../../Data/tree.pyv', 'rb') as val:
    t = pickle.load(val)
    print(t)
with open('../../Data/test.csv', 'r') as src:
    s = src.read().replace(',?', '')
with open('../../Data/test.csv', 'w') as dst:
    dst.write(s)
m = np.loadtxt('../../Data/test.csv', delimiter=',')
with open('../../Data/result.csv', 'w') as dst:
    for tag in de_tree.predict(t, m):
        dst.write('%d\n'%(tag))
