import sys

def allocate_and_copy():
    # Allocate first buffer of 1024 bytes
    buf = bytearray(1024)
    
    # Read up to 100 characters from stdin and copy into buf
    data = sys.stdin.read(100)
    for i in range(len(data)):
        buf[i] = ord(data[i])
        
    # Allocate second buffer of 1024 bytes
    buf1 = bytearray(1024)
    
    # Read next up to 100 characters from stdin and copy into buf1
    data = sys.stdin.read(100)
    for i in range(len(data)):
        buf1[i] = ord(data[i])

# To use the function, call allocate_and_copy()
if __name__ == "__main__":
    allocate_and_copy()