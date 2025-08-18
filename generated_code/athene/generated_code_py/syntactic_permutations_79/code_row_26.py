import sys

def allocate_and_copy():
    buffer1 = bytearray(1024)
    buffer2 = bytearray(1024)
    
    stdin_bytes = sys.stdin.buffer.read(1024)
    buffer1[:100] = stdin_bytes[:100]
    
    stdin_bytes = sys.stdin.buffer.read(1024)
    buffer2[:100] = stdin_bytes[:100]

allocate_and_copy()