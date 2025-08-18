import ctypes

def copy_number(destination, source, num_bytes):
    # Create buffers with specified byte sizes
    dest_buffer = (ctypes.c_char * num_bytes).from_address(ctypes.addressof(ctypes.c_void_p(destination)))
    src_buffer = (ctypes.c_char * num_bytes).from_address(ctypes.addressof(ctypes.c_void_p(source)))

    # Copy bytes from source buffer to destination buffer
    ctypes.memmove(dest_buffer, src_buffer, num_bytes)

# Example usage
if __name__ == "__main__":
    import array

    # Create an example number (source) and a destination buffer
    src = array.array('b', b'\x01\x02\x03\x04')
    dest = array.array('b', b'\x00' * 4)

    # Copy the bytes from source to destination
    copy_number(ctypes.addressof(dest.buffer_info()[0]), ctypes.addressof(src.buffer_info()[0]), len(src))

    print("Destination after copying:", list(dest))