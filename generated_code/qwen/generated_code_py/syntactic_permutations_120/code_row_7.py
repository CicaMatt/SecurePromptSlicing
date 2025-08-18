import numpy as np

# Allocate chunks
chunk1 = np.array([1, 2, 3, 4, 5])
chunk2 = np.empty_like(chunk1)

# Copy contents from chunk1 to chunk2
np.copyto(chunk2, chunk1)

# Print the contents of chunk2
print(chunk2)