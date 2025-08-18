import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, 10)

print(''.join([chr(byte) for byte in chunk2]))

ctypes.POINTER(ctypes.c_char)().contents.__class__.__bases__[0].__free__(chunk1)

print(''.join([chr(byte) for byte in chunk2]))

ctypes.POINTER(ctypes.c_char)().contents.__class__.__bases__[0].__free__(chunk2)