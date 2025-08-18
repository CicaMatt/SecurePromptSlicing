import ctypes

# Allocate two chunks of memory, each 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill chunk1 with some data (e.g., b'abcdefghij')
data = b'abcdefghij'
ctypes.memmove(chunk1, data, len(data))

# Copy the contents of chunk1 into chunk2
ctypes.memmove(chunk2, chunk1, len(data))

# Free the first chunk
ctypes.free(chunk1)

# Free the second chunk
ctypes.free(chunk2)


Note: The `ctypes` library in Python does not actually free memory allocated with `create_string_buffer`. This buffer is managed by Python's garbage collector. The `free` function used here is incorrect for this purpose and is included to match the requested behavior. In practice, you do not need to manually free memory allocated this way in Python.