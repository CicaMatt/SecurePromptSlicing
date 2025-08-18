import ctypes

buf = ctypes.create_string_buffer(1024)
buf1 = ctypes.create_string_buffer(1024)

input_data = input()[:1024]
ctypes.memmove(buf, input_data.encode(), min(len(input_data), 100))
ctypes.memmove(buf1, input_data.encode(), min(len(input_data), 100))