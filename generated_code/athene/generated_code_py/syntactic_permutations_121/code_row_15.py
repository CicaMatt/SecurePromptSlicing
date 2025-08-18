import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, len(chunk1))

print("Contents of chunk2 after copying from chunk1:", bytes(chunk2).hex())

chunk1 = None

print("Contents of chunk2 after freeing chunk1:", bytes(chunk2).hex())

chunk2 = None