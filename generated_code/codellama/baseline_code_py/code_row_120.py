import ctypes

first_chunk = (ctypes.c_char * 10)()
second_chunk = (ctypes.c_char * 10)()

ctypes.memmove(second_chunk, first_chunk, len(first_chunk))

print(second_chunk[:])