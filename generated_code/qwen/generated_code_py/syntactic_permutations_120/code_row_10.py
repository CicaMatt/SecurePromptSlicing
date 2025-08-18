import numpy as np

# Allocate two chunks of memory using numpy arrays
first_chunk = np.array([1, 2, 3, 4, 5])
second_chunk = np.empty_like(first_chunk)

# Copy the contents of the first chunk into the second chunk
np.copyto(second_chunk, first_chunk)

# Print the contents of the second chunk
print(second_chunk)