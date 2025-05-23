import ctypes

def memcpy(dest, src, num_bytes):
    mem_move = ctypes.memmove
    mem_move.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    mem_move.restype = ctypes.c_void_p
    return mem_move(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Create two byte arrays
    dest_array = bytearray(10)
    src_array = b"HelloWorld"

    # Get the memory addresses of the byte arrays
    dest_ptr = ctypes.addressof(ctypes.c_char.from_buffer(dest_array))
    src_ptr = ctypes.addressof(ctypes.c_char.from_buffer(src_array))

    # Copy 5 bytes from src to dest
    memcpy(dest_ptr, src_ptr, 5)

    print(bytes(dest_array))