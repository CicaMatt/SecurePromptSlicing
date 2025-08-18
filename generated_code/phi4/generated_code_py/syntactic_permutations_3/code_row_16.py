import ctypes

def copy_bytes(destination, source, num_bytes):
    # Create a ctypes array for the source if it's not already one
    if isinstance(source, str):
        source = (ctypes.c_char * len(source)).from_buffer_copy(source.encode('utf-8'))
    
    # Copy bytes from source to destination
    ctypes.memmove(destination, ctypes.addressof(source), num_bytes)

# Example usage:
source_string = "Hello"
destination_buffer = (ctypes.c_char * 10)()

# Call the function to copy bytes
copy_bytes(ctypes.addressof(destination_buffer), source_string, len(source_string))

# Convert destination buffer back to a Python string for display
copied_result = ctypes.string_at(ctypes.addressof(destination_buffer)).decode('utf-8')
print(copied_result)