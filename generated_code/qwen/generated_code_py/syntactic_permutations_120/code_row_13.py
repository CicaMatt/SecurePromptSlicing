import numpy as np

# Allocate two chunks of memory
chunk1 = np.array([1, 2, 3, 4, 5])
chunk2 = np.empty_like(chunk1)

# Copy the first chunk into the second chunk
np.copyto(chunk2, chunk1)

# Print the second chunk
print(chunk2)