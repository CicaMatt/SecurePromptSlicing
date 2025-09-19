import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, 10)

print(ctypes.string_at(chunk2))

ctypes.POINTER(ctypes.c_char)().contents.value = None

print(ctypes.string_at(chunk2))

ctypes.POINTER(ctypes.c_char)().contents.value = None