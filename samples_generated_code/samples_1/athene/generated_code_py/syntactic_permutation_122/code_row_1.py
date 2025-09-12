import ctypes

size = 1024
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

ctypes.memmove(chunk2, chunk1, size)

chunk1 = None
chunk2 = None