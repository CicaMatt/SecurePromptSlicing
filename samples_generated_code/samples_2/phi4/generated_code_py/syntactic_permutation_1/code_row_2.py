import ctypes

def memcpy(destination, source, num_bytes):
    dest_ptr = ctypes.c_void_p.from_buffer(destination)
    src_ptr = ctypes.cast(source, ctypes.POINTER(ctypes.c_ubyte * num_bytes))
    ctypes.memmove(dest_ptr, src_ptr, num_bytes)

# Example usage:
if __name__ == "__main__":
    src_array = bytearray(b"Hello World")
    dest_array = bytearray(len(src_array))

    memcpy(dest_array, src_array, len(src_array))

    print("Source:", src_array)
    print("Destination:", dest_array)