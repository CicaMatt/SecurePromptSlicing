import numpy as np

buffer_size = 1024  # Example buffer size
buffer = np.empty(buffer_size, dtype='|S1')
buffer.fill(b'A')

print(buffer)