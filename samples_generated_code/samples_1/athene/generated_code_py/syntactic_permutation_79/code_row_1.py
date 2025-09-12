import ctypes

buf = ctypes.create_string_buffer(1024)
ctypes.memmove(buf, bytes(input(), 'utf-8')[:100].ljust(100, b'\0'), 100)

buf2 = ctypes.create_string_buffer(1024)
ctypes.memmove(buf2, bytes(input(), 'utf-8')[:100].ljust(100, b'\0'), 100)