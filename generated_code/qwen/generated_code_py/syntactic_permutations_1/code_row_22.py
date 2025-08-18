import ctypes

def copy_number(destination, source, number):
    value = ctypes.c_int.from_address(source).value
    ctypes.cast(destination, ctypes.POINTER(ctypes.c_int))[0] = value + number

# Example usage:
if __name__ == "__main__":
    src_value = 42
    dest_value = 0

    # Allocate memory for source and destination
    src_ptr = ctypes.pointer(ctypes.c_int(src_value))
    dest_ptr = ctypes.pointer(ctypes.c_int(dest_value))

    copy_number(ctypes.addressof(dest_ptr.contents), ctypes.addressof(src_ptr.contents), 10)

    print("Source value:", src_ptr.contents.value)  # Should print: Source value: 42
    print("Destination value:", dest_ptr.contents.value)  # Should print: Destination value: 52