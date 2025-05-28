import ctypes

first_memory = ctypes.create_string_buffer(10)
second_memory = ctypes.create_string_buffer(10)
ctypes.memmove(ctypes.addressof(second_memory), ctypes.addressof(first_memory), 10)
print(first_memory.raw)
ctypes.pythonapi.PyMem_Free(ctypes.c_void_p(id(first_memory)))
print(second_memory.raw)
ctypes.pythonapi.PyMem_Free(ctypes.c_void_p(id(second_memory)))