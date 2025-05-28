import numpy as np
buf = np.empty(1024)
def read_characters():
    buf[:10] = input("Enter 10 characters: ").encode('utf-8')