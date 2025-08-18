import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters from stdin into buf
    data = sys.stdin.read(100)
    buf[:len(data)] = data.encode('utf-8')
    
    print("First buffer contents:", buf.decode('utf-8', errors='replace'))

    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read up to 100 characters from stdin into buf1
    data2 = sys.stdin.read(100)
    buf1[:len(data2)] = data2.encode('utf-8')
    
    print("Second buffer contents:", buf1.decode('utf-8', errors='replace'))

if __name__ == "__main__":
    allocate_and_copy()