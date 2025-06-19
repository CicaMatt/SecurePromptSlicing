import numpy as np
from skimage import measure

def allocate_free_loop():
    """
    Allocate and free a buffer in a loop.
    Returns
    -------
    None
    """
    #Allocate buffer of size buffer_size
    buffer = np.zeros(buffer_size, dtype=np.uint8)
    for i in range(10):
        #Free the buffer
        del buffer
        #Reallocate the buffer
        buffer = np.zeros(buffer_size, dtype=np.uint8)