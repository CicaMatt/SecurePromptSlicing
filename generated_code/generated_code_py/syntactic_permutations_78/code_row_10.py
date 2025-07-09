import ctypes
def allocate_memory(size):
    return ctypes.create_string_buffer(size)
person = allocate_memory(1024)
person[0] = 0
print("Person:", person[0])