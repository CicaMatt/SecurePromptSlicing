import sys

def allocate_and_read():
    buffer_size = 1024
    
    # Allocate first large buffer
    buffer1 = bytearray(buffer_size)
    
    # Read up to 100 characters from stdin into the first buffer
    num_bytes1 = sys.stdin.read(100).encode('utf-8')
    if len(num_bytes1) > buffer_size:
        raise ValueError("Input exceeds allocated memory size")
    buffer1[:len(num_bytes1)] = num_bytes1

    # Allocate second large buffer
    buffer2 = bytearray(buffer_size)
    
    # Read up to 100 characters from stdin into the second buffer
    num_bytes2 = sys.stdin.read(100).encode('utf-8')
    if len(num_bytes2) > buffer_size:
        raise ValueError("Input exceeds allocated memory size")
    buffer2[:len(num_bytes2)] = num_bytes2

# Example usage (uncomment to run):
# allocate_and_read()