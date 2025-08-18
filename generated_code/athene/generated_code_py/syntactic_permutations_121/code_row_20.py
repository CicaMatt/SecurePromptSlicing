import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(ord('a') + i).encode()

ctypes.memmove(chunk2, chunk1, len(chunk1))

print("Contents of chunk1:", b''.join(chunk1))
ctypes.POINTER(ctypes.c_char)().contents.__class__.__bases__[0].__free__(chunk1)

print("Contents of chunk2:", b''.join(chunk2))
ctypes.POINTER(ctypes.c_char)().contents.__class__.__bases__[0].__free__(chunk2)