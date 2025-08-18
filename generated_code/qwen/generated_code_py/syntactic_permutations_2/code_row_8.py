import ctypes

def copy_numbers(destination, source, count):
    c_source = (ctypes.c_int * len(source))(*source)
    c_destination = (ctypes.c_int * count)()
    
    ctypes.memmove(ctypes.addressof(c_destination), ctypes.addressof(c_source), count * ctypes.sizeof(ctypes.c_int))
    
    destination[:] = c_destination[:count]

# Example usage:
destination_buffer = [0] * 5
source_array = [1, 2, 3, 4, 5]
copy_numbers(destination_buffer, source_array, 5)
print(destination_buffer)