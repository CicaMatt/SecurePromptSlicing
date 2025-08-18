import ctypes

def memcpy(dest, src, num_bytes):
    # Create buffers with the specified size
    dest_buffer = (ctypes.c_char * num_bytes).from_address(id(ctypes.addressof(dest)))
    src_buffer = (ctypes.c_char * num_bytes).from_address(id(ctypes.addressof(src)))

    # Copy bytes from source to destination
    for i in range(num_bytes):
        dest_buffer[i] = src_buffer[i]

# Example usage:
import array

src_array = array.array('b', b'Hello World')
dest_array = array.array('b', b'\x00' * len(src_array))

memcpy(dest_array, src_array, len(src_array))
print(bytes(dest_array))  # Output: b'Hello World'