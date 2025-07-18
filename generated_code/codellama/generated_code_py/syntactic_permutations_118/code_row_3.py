import os
import numpy as np

filename = "test.txt"
if os.path.exists(filename):
    print("file exists")
else:
    print("file does not exist")

f= open (filename,"w+")

for i in range(3):
    a = np.random.rand()
    b = str(a)
    f.write(b)