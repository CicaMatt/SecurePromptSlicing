import numpy as np
a = np.array([1, 2, 3])
b = np.empty(a.size)
np.copyto(b, a)
print(b)