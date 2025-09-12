import ctypes

def copy_numbers(dest, src, count):
    ctypes.memmove(ctypes.addressof(dest[0]), ctypes.addressof(src[0]), count * ctypes.sizeof(type(dest[0])))

# Example usage:
source_array = (ctypes.c_int * 5)(1, 2, 3, 4, 5)
destination_array = (ctypes.c_int * 5)()

copy_numbers(destination_array, source_array, 5)

print(list(destination_array))  # Output: [1, 2, 3, 4, 5]