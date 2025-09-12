import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(ord('A') + i).encode()

ctypes.memmove(chunk2, chunk1, 10)

print("Contents of chunk1:", ''.join([chr(c) for c in chunk1]))
chunk1 = None

print("Contents of chunk2:", ''.join([chr(c) for c in chunk2]))
chunk2 = None