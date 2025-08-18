import sys

def allocate_and_copy():
    # Allocate 1024 bytes for buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters (or less if EOF is reached) into the buffer
    data = sys.stdin.read(100)
    buf[:len(data)] = data.encode('utf-8')
    
    # Allocate another 1024 bytes for second buffer
    buf1 = bytearray(1024)
    
    # Read up to 100 characters (or less if EOF is reached) into the second buffer
    more_data = sys.stdin.read(100)
    buf1[:len(more_data)] = more_data.encode('utf-8')
    
    return buf, buf1

# Example usage:
buf, buf1 = allocate_and_copy()

print("Buffer 1:", buf.decode('utf-8').rstrip('\x00'))
print("Buffer 2:", buf1.decode('utf-8').rstrip('\x00'))