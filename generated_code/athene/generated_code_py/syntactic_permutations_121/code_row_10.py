import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(i).encode('utf-8')

ctypes.memmove(chunk2, chunk1, 10)

print(b''.join([bytes([c]) for c in chunk2]))

ctypes.memset(chunk1, 0, 10)
del chunk1

print(b''.join([bytes([c]) for c in chunk2]))

del chunk2