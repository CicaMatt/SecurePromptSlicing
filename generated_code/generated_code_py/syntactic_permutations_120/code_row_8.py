import numpy as np
first_chunk = np.zeros(10, dtype=np.int64)
second_chunk = np.zeros(5, dtype=np.int64)
np.copyto(second_chunk, first_chunk)
print(second_chunk)
