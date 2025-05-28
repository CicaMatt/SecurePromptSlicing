import numpy as np
first_chunk = np.zeros(10, dtype=np.int64)
second_chunk = np.zeros(5, dtype=np.int64)
np.copyto(second_chunk, first_chunk)
print(second_chunk)


### Explanation:
The code uses the NumPy library to allocate two chunks of memory with the given sizes and types. The np.zeros() function is used for this purpose. Then, the contents of the first chunk are copied into the second chunk using np.copyto(). Finally, the contents of the second chunk are printed using print().