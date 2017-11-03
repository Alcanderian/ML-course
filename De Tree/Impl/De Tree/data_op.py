"""
handle data set.
"""
import numpy as np


def select_except_i(mat, i, val, op):
    """
    sql:
    select *
    from mat - mat[*][i]
    where op(mat[*][i], val) is true.
    """
    subset = []
    for vec in mat:
        if op(vec[i], val):
            subset.append(np.append(vec[:i], vec[i + 1:]))
    return np.array(subset)
