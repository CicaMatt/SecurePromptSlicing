import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 1024 characters into the first buffer
    data = sys.stdin.read(100)
    buf[:len(data)] = data.encode('utf-8')
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read up to 1024 characters into the second buffer
    data2 = sys.stdin.read(100)
    buf1[:len(data2)] = data2.encode('utf-8')

if __name__ == "__main__":
    allocate_and_copy()