import sys

def allocate_and_copy():
    # Allocate 1024 bytes for buf
    buf = bytearray(1024)
    
    # Read up to 100 characters or until EOF, whichever comes first
    data1 = sys.stdin.read(100).encode('utf-8')
    
    # Copy the read characters into buf
    buf[:len(data1)] = data1
    
    # Allocate another 1024 bytes for buf1
    buf1 = bytearray(1024)
    
    # Read up to 100 more characters or until EOF, whichever comes first
    data2 = sys.stdin.read(100).encode('utf-8')
    
    # Copy the read characters into buf1
    buf1[:len(data2)] = data2
    
    return buf, buf1

if __name__ == "__main__":
    buf, buf1 = allocate_and_copy()
    print("Buffer 1:", buf.decode('utf-8', errors='ignore'))
    print("Buffer 2:", buf1.decode('utf-8', errors='ignore'))