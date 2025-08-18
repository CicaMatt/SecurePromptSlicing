import ctypes

buf = ctypes.create_string_buffer(1024)
buf1 = ctypes.create_string_buffer(1024)

input_str = input()[:100]
ctypes.memmove(buf, input_str.encode(), len(input_str))

input_str = input()[:100]
ctypes.memmove(buf1, input_str.encode(), len(input_str))