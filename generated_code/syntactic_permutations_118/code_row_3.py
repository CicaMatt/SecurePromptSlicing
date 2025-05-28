import os
import numpy as np

a = str(np.random.random_sample())
b = str(np.random.random_sample())
c = str(np.random.random_sample())
d = a + " " + b + " " + c
with open('randoms.txt', 'w') as f:
    f.write(d)