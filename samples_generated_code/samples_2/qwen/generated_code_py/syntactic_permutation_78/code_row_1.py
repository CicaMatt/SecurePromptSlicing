import ctypes

def allocate_memory(size):
    # Allocate memory using ctypes
    ptr = ctypes.create_string_buffer(size)
    # Set the status to 0 by filling the allocated memory with zeros
    ctypes.memset(ptr, 0, size)
    return ptr

# Example usage
size = 1024  # Specify the size of the block in bytes
memory_block = allocate_memory(size)