import sys

def allocate_and_copy():
    # Allocate 1024 bytes for the first buffer
    buf = bytearray(1024)
    
    # Read up to 1024 bytes from stdin into the first buffer
    data = sys.stdin.read(100)
    buf[:len(data)] = data.encode('utf-8')
    
    # Allocate another 1024 bytes for the second buffer
    buf1 = bytearray(1024)

    return buf, buf1

if __name__ == "__main__":
    allocate_and_copy()