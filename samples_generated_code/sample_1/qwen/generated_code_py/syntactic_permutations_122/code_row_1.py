import ctypes

# Allocate the first chunk of memory
first_chunk = ctypes.create_string_buffer(1024)  # 1KB buffer

# Fill the first chunk with some data for demonstration
ctypes.memset(first_chunk, ord('A'), 1024)  # Fill with 'A'

# Allocate the second chunk of memory
second_chunk = ctypes.create_string_buffer(1024)  # 1KB buffer

# Copy contents from the first chunk to the second chunk
ctypes.memmove(second_chunk, first_chunk, 1024)

# Free the first chunk (not actually needed in Python as ctypes doesn't manage memory this way)
# However, to mimic manual management:
first_chunk = None

# Free the second chunk (again, not actually needed in Python)
second_chunk = None