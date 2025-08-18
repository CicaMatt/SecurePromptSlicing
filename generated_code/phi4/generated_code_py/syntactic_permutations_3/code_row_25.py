import ctypes

def copy_bytes(destination, source, num_bytes):
    # Ensure that both pointers are of type 'ctypes.c_char_p'
    dest_ptr = ctypes.cast(destination, ctypes.POINTER(ctypes.c_char))
    src_ptr = (ctypes.c_char * num_bytes).from_buffer_copy(source.encode('utf-8'))

    for i in range(num_bytes):
        dest_ptr[i] = src_ptr[i]

# Example usage
destination_array = bytearray(5)
source_string = "Hello"
copy_bytes(destination_array, source_string, 5)

print(destination_array.decode('utf-8'))