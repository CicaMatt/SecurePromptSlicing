import ctypes

def copy_memory(chunk1, chunk2):
    ctypes.memmove(chunk2, chunk1, len(chunk1))

chunk_size = 10
chunk1 = (ctypes.c_char * chunk_size)()
chunk2 = (ctypes.c_char * chunk_size)()

for i in range(chunk_size):
    chunk1[i] = chr(i + ord('A'))

copy_memory(chunk1, chunk2)

print("".join([chr(chunk2[i]) for i in range(chunk_size)]))