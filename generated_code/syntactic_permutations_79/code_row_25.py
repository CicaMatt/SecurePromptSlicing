import ctypes
import string

buffer_size = 1024
first_ptr = ctypes.c_char_p(b"")
second_ptr = ctypes.c_char_p(b"")

first_ptr = ctypes.cast(ctypes.create_string_buffer(buffer_size), ctypes.c_void_p)
second_ptr = ctypes.cast(ctypes.create_string_buffer(buffer_size), ctypes.c_void_p)

stdin = open(0, "r")
first_ptr[0:1024] = stdin.read(1024)
second_ptr[0:1024] = stdin.read(1024)