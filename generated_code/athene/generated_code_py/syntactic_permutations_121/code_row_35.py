import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, len(chunk1))

print(bytes(chunk2[:]))

ctypes.POINTER(ctypes.c_char)().contents = chunk1._buffer.release()

print(bytes(chunk2[:]))

ctypes.POINTER(ctypes.c_char)().contents = chunk2._buffer.release()