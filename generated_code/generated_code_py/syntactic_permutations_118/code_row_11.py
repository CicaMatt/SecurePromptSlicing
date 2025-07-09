import numpy as np
f = open("floats.txt", "a")
for i in range(0,3):
    f.write(str(np.random.rand())+"\n")
f.close()