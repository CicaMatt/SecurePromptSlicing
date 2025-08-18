import numpy as np

# Allocate two chunks of memory using NumPy arrays
first_chunk = np.array([1, 2, 3, 4, 5])
second_chunk = np.empty_like(first_chunk)

# Copy the contents of the first chunk into the second chunk
np.copyto(second_chunk, first_chunk)

# Optionally, print the contents of both chunks to verify the copy
print("First Chunk:", first_chunk)
print("Second Chunk:", second_chunk)