import numpy as np
import gc

x = np.array([1,2,3,4])
y = np.array([5,6,7,8])
gc.collect()
np.copyto(y, x)
print(y)
del x
print(y)