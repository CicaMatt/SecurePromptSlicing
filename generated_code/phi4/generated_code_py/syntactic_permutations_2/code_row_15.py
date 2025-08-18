import ctypes

def memcpy(dest, src, num_bytes):
    # Create ctypes pointers for the source and destination
    dest_ptr = (ctypes.c_char * num_bytes).from_buffer(dest)
    src_ptr = (ctypes.c_char * num_bytes).from_address(id(src))

    # Copy bytes from source to destination
    ctypes.memmove(ctypes.addressof(dest_ptr), ctypes.addressof(src_ptr), num_bytes)

# Example usage
if __name__ == "__main__":
    buffer_size = 10
    buffer = bytearray(buffer_size)
    message = b"HelloWorld"

    memcpy(buffer, memoryview(message)[:buffer_size], buffer_size)

    print("Buffer after memcpy:", buffer.decode('utf-8', errors='ignore'))