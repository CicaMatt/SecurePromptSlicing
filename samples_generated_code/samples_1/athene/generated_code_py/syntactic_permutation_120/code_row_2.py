import ctypes

chunk_size = 1024
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

for i in range(chunk_size):
    first_chunk[i] = chr(i % 256).encode('latin-1')

ctypes.memmove(second_chunk, first_chunk, chunk_size)

print(bytes(second_chunk))