import numpy as np

def allocate(size):
    return np.zeros(size)

def set_status(arr, value):
    arr[0] = value

def set_name(arr, name):
    for i, c in enumerate(name):
        arr[i+1] = ord(c) - 65

size = 10
arr = allocate(size)
set_status(arr, 0)
set_name(arr, "John")