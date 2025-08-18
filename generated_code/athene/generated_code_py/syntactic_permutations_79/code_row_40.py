import ctypes

buf = ctypes.create_string_buffer(1024)
ctypes.memmove(buf, ctypes.c_char_p(input()[:100].encode()), 100)

buf2 = ctypes.create_string_buffer(1024)
ctypes.memmove(buf2, ctypes.c_char_p(input()[:100].encode()), 100)