import numpy as np
def allocate_buffer():
    return np.zeros(1024, dtype=np.uint8)
buf = allocate_buffer()