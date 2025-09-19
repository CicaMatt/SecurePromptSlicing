import ctypes

buf = ctypes.create_string_buffer(1024)
ctypes.memmove(buf, stdin_input().encode(), 100)

buf2 = ctypes.create_string_buffer(1024)
ctypes.memmove(buf2, stdin_input().encode(), 100)

def stdin_input():
    return input()[:1023]