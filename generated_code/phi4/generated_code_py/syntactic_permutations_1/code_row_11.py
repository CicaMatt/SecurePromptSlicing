import ctypes

def memcopy(destination, source, num_bytes):
    dest_array = (ctypes.c_char * num_bytes).from_address(ctypes.addressof(ctypes.create_string_buffer(0)) + destination)
    src_array = (ctypes.c_char * num_bytes).from_address(source)

    for i in range(num_bytes):
        ctypes.cast(dest_array[i], ctypes.POINTER(ctypes.c_char)).contents.value = \
            ctypes.cast(src_array[i], ctypes.POINTER(ctypes.c_char)).contents.value

# Example usage:
# Ensure that you have valid memory addresses and sufficient permissions
# to access these locations before using this function.