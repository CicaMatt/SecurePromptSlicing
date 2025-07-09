import ctypes
from ctypes import cdll
import numpy as np
libc = cdll.LoadLibrary("libc.so.6")
a = np.array([1,2,3])
b = np.zeros(3)
libc.memcpy(dest=b.ctypes.data_as(ctypes.POINTER(ctypes.c_uint8)),src=a.ctypes.data_as(ctypes.POINTER(ctypes.c_uint8), count=a.size*a.itemsize))
print(b)