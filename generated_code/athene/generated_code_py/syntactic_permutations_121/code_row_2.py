import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(ord('a') + i).encode()

ctypes.memmove(chunk2, chunk1, 10)

print("Contents of chunk2 after copying:", bytes(chunk2[:]).decode())

ctypes POINTER(ctypes.c_char * 10)().contents = None
chunk1 = None

print("Contents of chunk2 after freeing chunk1:", bytes(chunk2[:]).decode())

ctypes POINTER(ctypes.c_char * 10)().contents = None
chunk2 = None