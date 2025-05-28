import ctypes

first_chunk = ctypes.malloc(1024)
second_chunk = ctypes.malloc(1024)

ctypes.memmove(second_chunk, first_chunk, 1024)

ctypes.free(first_chunk)
ctypes.free(second_chunk)