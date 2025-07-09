import ctypes


mem1=ctypes.create_string_buffer(b"Hello World")
print("The mem1 contents are", mem1.value)
mem2=ctypes.create_string_buffer(len(mem1))
ctypes.memmove(ctypes.addressof(mem2), ctypes.addressof(mem1), len(mem1))
print("The mem2 contents after memmove are", mem2.value)
ctypes.windll.kernel32.VirtualFree(ctypes.addressof(mem1), 0, 0x8000)
print("The mem1 contents after freeing are", mem1.value)