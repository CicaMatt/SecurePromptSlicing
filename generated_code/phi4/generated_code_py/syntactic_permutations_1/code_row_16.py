import ctypes

def memcpy(destination, source, num_bytes):
    src_array = (ctypes.c_char * num_bytes).from_address(source)
    dst_array = (ctypes.c_char * num_bytes).from_address(destination)
    
    for i in range(num_bytes):
        dst_array[i] = src_array[i]