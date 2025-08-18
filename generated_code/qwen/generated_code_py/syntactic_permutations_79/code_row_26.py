import sys

def allocate_and_copy():
    buffer_size = 1024
    
    # Allocate first buffer and read 100 characters from stdin
    buffer1 = bytearray(buffer_size)
    sys.stdin.buffer.readinto(buffer1[:100])
    
    # Allocate second buffer and read another 100 characters from stdin
    buffer2 = bytearray(buffer_size)
    sys.stdin.buffer.readinto(buffer2[:100])
    
    return buffer1, buffer2

# Example usage
if __name__ == "__main__":
    buffer1, buffer2 = allocate_and_copy()