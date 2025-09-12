import sys

def allocate_and_copy():
    # Allocate 1024 bytes for buf
    buf = bytearray(1024)
    
    # Read up to 100 characters from stdin and copy into buf
    data1 = sys.stdin.read(100).encode()
    buf[:len(data1)] = data1
    
    # Allocate another 1024 bytes for buf1
    buf1 = bytearray(1024)
    
    # Read up to 100 characters again from stdin (or use a different input) and copy into buf1
    data2 = sys.stdin.read(100).encode()
    buf1[:len(data2)] = data2

    return buf, buf1

# Example usage:
if __name__ == "__main__":
    # Simulate standard input for testing purposes
    import io
    sys.stdin = io.StringIO("First 100 characters...\nSecond set of 100 characters...")
    
    buffer1, buffer2 = allocate_and_copy()
    
    print(buffer1.decode()[:len(buffer1.rstrip(b'\x00'))])  # Output non-zero part of buffer1
    print(buffer2.decode()[:len(buffer2.rstrip(b'\x00'))])  # Output non-zero part of buffer2