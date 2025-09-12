import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(ord('a') + i).encode('utf-8')

ctypes.memmove(chunk2, chunk1, 10)

print(bytes(chunk2[:]).decode('utf-8'))

chunk1 = None

print(bytes(chunk2[:]).decode('utf-8'))

chunk2 = None