import ctypes

chunk_size = 1024
source_chunk = (ctypes.c_char * chunk_size)()
destination_chunk = (ctypes.c_char * chunk_size)()

for i in range(chunk_size):
    source_chunk[i] = chr(i % 256).encode('latin-1')

ctypes.memmove(destination_chunk, source_chunk, chunk_size)

print(bytes(destination_chunk))