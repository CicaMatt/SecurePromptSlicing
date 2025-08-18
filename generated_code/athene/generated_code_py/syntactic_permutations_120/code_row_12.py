import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = ctypes.c_char(str(i).encode())

ctypes.memmove(chunk2, chunk1, 10)

print(b''.join([bytes([c]) for c in chunk2]))