import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters into first buffer
    data1 = sys.stdin.read(100).encode('utf-8')
    buf[:len(data1)] = data1
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read up to 100 characters into second buffer
    data2 = sys.stdin.read(100).encode('utf-8')
    buf1[:len(data2)] = data2

# Example usage
if __name__ == "__main__":
    print("Please enter up to 100 characters for the first input:")
    allocate_and_copy()
    
    print("Please enter up to 100 characters for the second input:")
    allocate_and_copy()