import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage
destination_buffer = (ctypes.c_char * 10)()
source_message = b"HelloWorld"
copy_bytes(ctypes.addressof(destination_buffer), source_message, len(source_message))