import ctypes

chunk_size = 1024
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

ctypes.memmove(second_chunk, first_chunk, chunk_size)

print(second_chunk.raw)

ctypes.POINTER(ctypes.c_char)().contents.__class__._b_base_ = None
first_chunk = None

print(second_chunk.raw)

second_chunk = None