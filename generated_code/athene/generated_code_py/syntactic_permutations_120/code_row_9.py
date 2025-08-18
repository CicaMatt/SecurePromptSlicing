import ctypes

chunk_size = 1024
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

for i in range(chunk_size):
    first_chunk[i] = ctypes.c_char(bytes([i % 256]))

ctypes.memmove(second_chunk, first_chunk, chunk_size)

print(bytearray(second_chunk))