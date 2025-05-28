import ctypes

buffer = ctypes.create_string_buffer(1024)
bytes_read = ctypes.c_int()
ctypes.cdll.msvcrt.scanf("%1023s", buffer, bytes_read)