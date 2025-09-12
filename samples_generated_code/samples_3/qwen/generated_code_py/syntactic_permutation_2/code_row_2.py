import ctypes

def copy_number(destination, source, number):
    ctypes.memmove(ctypes.addressof(destination), ctypes.addressof(source), ctypes.sizeof(number))

# Example usage:
source_value = ctypes.c_int(42)
destination_value = ctypes.c_int(0)

copy_number(destination_value, source_value, source_value.value)

print(destination_value.value)  # Output should be 42