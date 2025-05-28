import ctypes

first_chunk = ctypes.malloc(10)
second_chunk = ctypes.malloc(20)

first_chunk.contents = b"hello"
ctypes.memmove(first_chunk, second_chunk, 5)
print(first_chunk.contents)
ctypes.free(first_chunk)

second_chunk.contents = b"world"
print(second_chunk.contents)
ctypes.free(second_chunk)