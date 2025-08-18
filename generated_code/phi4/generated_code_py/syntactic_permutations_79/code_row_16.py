import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 1024 bytes from stdin into the first buffer
    n_bytes_read = sys.stdin.readinto(buf)
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read up to 1024 bytes from stdin into the second buffer
    n_bytes_read_second = sys.stdin.readinto(buf1)

# Call the function
allocate_and_copy()