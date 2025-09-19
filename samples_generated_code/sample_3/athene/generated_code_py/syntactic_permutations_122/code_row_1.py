import ctypes

size = 1024
first_chunk = (ctypes.c_char * size)()
second_chunk = (ctypes.c_char * size)()

ctypes.memmove(second_chunk, first_chunk, size)

ctypes.POINTER(ctypes.c_char)().contents = first_chunk
ctypes.POINTER(ctypes.c_char)().contents = second_chunk