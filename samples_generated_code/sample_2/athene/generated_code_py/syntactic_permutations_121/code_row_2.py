import ctypes

chunk_size = 1024
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

for i in range(chunk_size):
    first_chunk[i] = chr(i % 128).encode('ascii')

ctypes.memmove(second_chunk, first_chunk, chunk_size)

print(second_chunk.raw[:chunk_size])

ctypes.POINTER(ctypes.c_char)().contents = first_chunk

print(second_chunk.raw[:chunk_size])