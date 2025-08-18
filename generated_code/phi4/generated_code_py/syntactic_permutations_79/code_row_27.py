import sys

def allocate_memory():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters into the first buffer
    data = sys.stdin.read(100)
    buf[:len(data)] = data.encode('utf-8')
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read up to 100 characters into the second buffer
    data1 = sys.stdin.read(100)
    buf1[:len(data1)] = data1.encode('utf-8')

if __name__ == "__main__":
    allocate_memory()