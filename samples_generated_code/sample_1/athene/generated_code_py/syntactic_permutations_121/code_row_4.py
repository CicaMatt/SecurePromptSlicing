import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = ctypes.c_char(b'A')

ctypes.memmove(chunk2, chunk1, 10)

print("Contents of chunk2 after copying:", bytes(chunk2))

ctypes.POINTER(ctypes.c_char).from_buffer(chunk1)._buffer = None

print("Contents of chunk2 after freeing chunk1:", bytes(chunk2))

ctypes.POINTER(ctypes.c_char).from_buffer(chunk2)._buffer = None