import ctypes

first_chunk = (ctypes.c_char * 8)()
second_chunk = (ctypes.c_char * 8)()

ctypes.memmove(second_chunk, first_chunk, 8)
print(second_chunk)

first_chunk = None
print(second_chunk)

second_chunk = None