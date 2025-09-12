import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters into buf
    data = sys.stdin.read(100)
    buf[:len(data)] = data.encode('utf-8')
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read up to another 100 characters into buf1
    data = sys.stdin.read(100)
    buf1[:len(data)] = data.encode('utf-8')

# Example usage:
if __name__ == "__main__":
    print("Enter up to 200 characters (two lines for the two buffers):")
    allocate_and_copy()