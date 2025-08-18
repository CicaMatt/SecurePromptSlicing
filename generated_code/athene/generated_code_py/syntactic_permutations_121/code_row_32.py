import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(i).encode('utf-8')

ctypes.memmove(chunk2, chunk1, len(chunk1))

print("Chunk2 after copy:", bytes(chunk2[:]))

chunk1 = None

print("Chunk2 after freeing chunk1:", bytes(chunk2[:]))

chunk2 = None