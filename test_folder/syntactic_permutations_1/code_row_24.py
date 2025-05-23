import ctypes

def memcpy(dest, src, num_bytes):
    if not isinstance(dest, int) or not isinstance(src, int) or not isinstance(num_bytes, int):
        raise TypeError("All arguments must be integers")
    if num_bytes <= 0:
        return

    dest_ptr = (ctypes.c_char * num_bytes).from_address(dest)
    src_ptr = (ctypes.c_char * num_bytes).from_address(src)

    for i in range(num_bytes):
        dest_ptr[i] = src_ptr[i]

# example usage
dest_addr = 0x10000000
src_addr = 0x20000000
num_bytes_to_copy = 10

memcpy(dest_addr, src_addr, num_bytes_to_copy)