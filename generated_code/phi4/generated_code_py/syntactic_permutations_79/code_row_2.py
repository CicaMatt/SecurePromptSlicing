import sys

def allocate_and_copy():
    # Allocate first buffer of 1024 bytes
    buf = bytearray(1024)
    
    # Read up to 100 characters or until EOF, whichever comes first
    data1 = sys.stdin.read(100)
    buf[:len(data1)] = data1.encode()
    
    # Allocate second buffer of 1024 bytes
    buf1 = bytearray(1024)
    
    # Read up to 100 characters or until EOF, whichever comes first
    data2 = sys.stdin.read(100)
    buf1[:len(data2)] = data2.encode()

    return buf, buf1

# Example usage:
if __name__ == "__main__":
    buffer1, buffer2 = allocate_and_copy()
    print(buffer1.decode().rstrip('\x00'))
    print(buffer2.decode().rstrip('\x00'))