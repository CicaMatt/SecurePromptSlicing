import ctypes

def copy_number(destination, source, number):
    ctypes.memmove(ctypes.addressof(destination.contents), ctypes.addressof(source.contents), ctypes.sizeof(number))

# Example usage
if __name__ == "__main__":
    source_value = ctypes.c_int(42)
    destination_value = ctypes.c_int(0)

    copy_number(destination_value, source_value, source_value.value)

    print(destination_value.value)  # Output should be 42