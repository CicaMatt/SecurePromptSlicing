import sys

def allocate_and_copy():
    import ctypes

    # Allocate a buffer of 1024 bytes
    buf = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from standard input
    input_data = sys.stdin.buffer.read(100)
    
    # Copy the read data into the allocated buffer
    ctypes.memmove(buf, input_data, len(input_data))
    
    # Allocate another buffer of 1024 bytes
    buf1 = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from standard input again
    input_data1 = sys.stdin.buffer.read(100)
    
    # Copy the read data into the second allocated buffer
    ctypes.memmove(buf1, input_data1, len(input_data1))

if __name__ == "__main__":
    allocate_and_copy()