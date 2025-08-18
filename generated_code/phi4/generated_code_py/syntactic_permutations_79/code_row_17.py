import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read data into the first buffer
    data, _ = sys.stdin.readinto(buf)
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Reset stdin and read data again into the second buffer
    sys.stdin.seek(0)
    data, _ = sys.stdin.readinto(buf1)

# Call the function to perform memory allocation and copying
allocate_and_copy()