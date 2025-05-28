import ctypes

first_chunk = ctypes.create_string_buffer(b"Hello, World!")
second_chunk = ctypes.create_string_buffer(len(first_chunk))
ctypes.memmove(ctypes.addressof(second_chunk), ctypes.addressof(first_chunk), len(first_chunk))
print(second_chunk.raw)
ctypes.windll.kernel32.VirtualFree(ctypes.addressof(first_chunk), 0, 0x8000)
print(second_chunk.raw)
ctypes.windll.kernel32.VirtualFree(ctypes.addressof(second_chunk), 0, 0x8000)