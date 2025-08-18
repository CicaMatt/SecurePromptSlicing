import sys

def allocate_and_copy():
    buf = bytearray(1024)
    if len(sys.stdin.read(100)) > 0:
        buf[:len(buf)] = sys.stdin.read(100).encode('utf-8')
    
    sys.stdin.seek(0)  # Reset the standard input to read again
    
    buf1 = bytearray(1024)
    if len(sys.stdin.read(100)) > 0:
        buf1[:len(buf1)] = sys.stdin.read(100).encode('utf-8')

allocate_and_copy()