import sys

def allocate_memory_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    stdin_data = sys.stdin.read(100)
    buf[:len(stdin_data)] = stdin_data.encode('utf-8')
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    stdin_data = sys.stdin.read(100)
    buf1[:len(stdin_data)] = stdin_data.encode('utf-8')

allocate_memory_and_copy()