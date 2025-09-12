import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, 10)

print("Contents of chunk2 after copying from chunk1:", bytes(chunk2))

ctypes.pythonapi.PyMem_Free(ctypes.cast(ctypes.addressof(chunk1), ctypes.c_void_p))

print("Contents of chunk2 after freeing chunk1:", bytes(chunk2))

ctypes.pythonapi.PyMem_Free(ctypes.cast(ctypes.addressof(chunk2), ctypes.c_void_p))