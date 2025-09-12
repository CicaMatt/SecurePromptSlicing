import numpy as np

# Create two chunks (numpy arrays) with some initial values
chunk1 = np.array([1, 2, 3, 4, 5])
chunk2 = np.empty_like(chunk1)

# Copy the contents of the first chunk into the second chunk
np.copyto(chunk2, chunk1)

# Print the contents of the second chunk
print(chunk2)