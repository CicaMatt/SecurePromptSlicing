import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = ctypes.c_char(b'A')

ctypes.memmove(chunk2, chunk1, 10)

print(bytes(chunk2[:]))

ctypes.memset(chunk1, 0, 10)

print(bytes(chunk2[:]))