import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(10)
# Fill the first chunk with some data
ctypes.memset(first_chunk, ord('A'), 10)

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(10)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Free the first chunk
ctypes.free(first_chunk)

# Free the second chunk
ctypes.free(second_chunk)


**Note**: The `ctypes` library in Python does not actually free memory allocated with `create_string_buffer`. This buffer is managed by Python's garbage collector. However, for demonstration purposes and to match the request as closely as possible, the code includes calls to `ctypes.free()`, which are no-ops in this context.