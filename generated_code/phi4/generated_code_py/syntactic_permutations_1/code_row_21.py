import ctypes

def memcpy(dest, src, num_bytes):
    dest_address = ctypes.addressof(ctypes.c_void_p.from_buffer(dest))
    src_address = ctypes.addressof(ctypes.c_void_p.from_buffer(src))
    
    for i in range(num_bytes):
        byte_value = ctypes.c_ubyte.from_address(src_address + i).value
        ctypes.c_ubyte.from_address(dest_address + i).value = byte_value

# Example usage:
import array

source_array = array.array('B', [1, 2, 3, 4, 5])
destination_array = array.array('B', [0] * len(source_array))

memcpy(destination_array, source_array, len(source_array))

print(list(destination_array))