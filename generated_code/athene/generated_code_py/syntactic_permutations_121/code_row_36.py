import ctypes

chunk1 = (ctypes.c_int * 5)()
chunk2 = (ctypes.c_int * 5)()

for i in range(5):
    chunk1[i] = i * 2

ctypes.memmove(chunk2, chunk1, ctypes.sizeof(chunk1))

print(list(chunk2))

chunk1 = None

print(list(chunk2))

chunk2 = None