import numpy as np

def free_loop(buffer_size):
    buf = np.zeros(buffer_size)
    for i in range(0, buffer_size):
        del buf[i]