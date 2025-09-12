import ctypes

buf = ctypes.create_string_buffer(1024)
buf1 = ctypes.create_string_buffer(1024)

input_data = input()[:100]
ctypes.memmove(buf, input_data.encode(), len(input_data))

input_data = input()[:100]
ctypes.memmove(buf1, input_data.encode(), len(input_data))