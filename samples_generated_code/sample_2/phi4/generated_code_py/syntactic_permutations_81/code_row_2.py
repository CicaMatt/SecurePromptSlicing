import sys

def allocate_memory_and_read():
    # Allocate buffer to hold 10 characters
    buf = bytearray(10)
    
    # Read up to 10 bytes from standard input
    n = sys.stdin.readinto(buf)
    
    # Truncate the buffer if less than 10 characters are read
    buf = buf[:n]
    
    return buf

if __name__ == "__main__":
    buffer_content = allocate_memory_and_read()
    print("Buffer content:", buffer_content.decode('utf-8'))