import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, 10)
print("Contents of chunk2:", bytes(chunk2))

chunk1 = None  # Free memory by setting reference to None
print("Contents of chunk2 after freeing chunk1:", bytes(chunk2))

chunk2 = None  # Free memory by setting reference to None