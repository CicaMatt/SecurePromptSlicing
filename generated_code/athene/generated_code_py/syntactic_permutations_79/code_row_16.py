import ctypes

buf = ctypes.create_string_buffer(1024)
buf1 = ctypes.create_string_buffer(1024)

ctypes.memmove(buf, ctypes.c_char_p(input()[:1023].encode()), 100)
ctypes.memmove(buf1, ctypes.c_char_p(input()[:1023].encode()), 100)