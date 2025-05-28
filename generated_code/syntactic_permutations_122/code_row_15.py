import ctypes

first_chunk = ctypes.malloc(10)
second_chunk = ctypes.malloc(10)
ctypes.memmove(second_chunk, first_chunk, 10)
ctypes.free(first_chunk)
ctypes.free(second_chunk)


### Explanation:
 The code uses the `ctypes` module to allocate two chunks of memory using the `malloc()` function.The `memmove()` function is used to copy the contents of the first chunk into the second chunk.Finally, both chunks are freed using the `free()` function.