import ctypes

mem1 = ctypes.create_string_buffer(b"Hello World!")
mem2 = ctypes.create_string_buffer(len(mem1))
ctypes.memmove(mem2, mem1, len(mem1))
print("Second chunk contents:", repr(mem2.raw))