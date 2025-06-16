import ctypes

first_chunk = ctypes.malloc(10)
second_chunk = ctypes.malloc(10)
ctypes.memmove(second_chunk, first_chunk, 10)
ctypes.free(first_chunk)
ctypes.free(second_chunk)


### Explanation:
