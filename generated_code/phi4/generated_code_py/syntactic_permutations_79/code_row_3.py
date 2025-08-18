import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters into buf
    read_data = sys.stdin.read(100)
    buf[:len(read_data)] = read_data.encode()

    # Allocate second buffer
    buf1 = bytearray(1024)

    # Read another up to 100 characters into buf1
    read_data = sys.stdin.read(100)
    buf1[:len(read_data)] = read_data.encode()

# Example of how the function can be called (uncomment and run in a context where stdin provides input):
# allocate_and_copy()