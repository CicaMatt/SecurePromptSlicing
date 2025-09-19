import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = ctypes.c_char(bytes([i]))

ctypes.memmove(chunk2, chunk1, 10)

print("Contents of second chunk after copy:", bytes(chunk2))

ctypes.pythonapi.free(ctypes.cast(chunk1, ctypes.c_void_p))

print("Contents of second chunk after freeing first chunk:", bytes(chunk2))

ctypes.pythonapi.free(ctypes.cast(chunk2, ctypes.c_void_p))