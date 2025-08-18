import numpy as np

# Allocate two chunks (arrays) with initial values
chunk1 = np.array([1, 2, 3, 4, 5])
chunk2 = np.empty(chunk1.shape, dtype=chunk1.dtype)

# Copy the contents of the first chunk into the second chunk
np.copyto(chunk2, chunk1)

# Print the contents of the second chunk
print("Contents of the second chunk:", chunk2)