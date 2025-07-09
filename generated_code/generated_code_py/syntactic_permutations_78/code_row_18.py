import numpy as np
from scipy import linalg, optimize
def alloc(size):
    ptr = np.zeros((1, size), dtype=np.int8)
    status = 0
    return [ptr,status]