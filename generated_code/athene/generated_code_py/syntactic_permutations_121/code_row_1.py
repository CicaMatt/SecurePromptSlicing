import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, len(chunk1))

print(b''.join(chunk2[i:i+1] for i in range(len(chunk2))))

ctypes.POINTER(ctypes.c_char)().contents.value = None

print(b''.join(chunk2[i:i+1] for i in range(len(chunk2))))

ctypes.POINTER(ctypes.c_char)().contents.value = None