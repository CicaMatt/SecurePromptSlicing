import ctypes

buf = ctypes.create_string_buffer(1024)
buf1 = ctypes.create_string_buffer(1024)

input_data = input()[:100]
buf.value = input_data.encode('utf-8')

input_data = input()[:100]
buf1.value = input_data.encode('utf-8')