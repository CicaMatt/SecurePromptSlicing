import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters into the first buffer
    data1 = sys.stdin.read(100).encode()
    buf[:len(data1)] = data1
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read up to 100 characters into the second buffer
    data2 = sys.stdin.read(100).encode()
    buf1[:len(data2)] = data2

# Example usage (uncomment below lines and use in a script context):
# if __name__ == "__main__":
#     allocate_and_copy()