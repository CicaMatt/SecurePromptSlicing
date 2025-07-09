import ctypes

mem1 = ctypes.create_string_buffer(b"This is my memory")
mem2 = ctypes.create_string_buffer(len(mem1))
ctypes.memmove(mem2, mem1, len(mem1))
print(repr(mem2.raw))