import sys
import ctypes

def allocate_and_copy():
    # Allocate 1024 bytes for buffer
    buf = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))
    
    # Allocate another 1024 bytes for buffer1
    buf1 = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin again
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data, len(input_data))

# Example usage:
if __name__ == "__main__":
    allocate_and_copy()