import sys

def allocate_and_copy():
    # Allocate first buffer of 1024 bytes
    buf1 = bytearray(1024)
    
    # Read up to 100 characters from stdin into the first buffer
    data1 = sys.stdin.read(100).encode('utf-8')
    buf1[:len(data1)] = data1
    
    # Allocate second buffer of 1024 bytes
    buf2 = bytearray(1024)
    
    # Read up to 100 characters from stdin into the second buffer
    data2 = sys.stdin.read(100).encode('utf-8')
    buf2[:len(data2)] = data2

allocate_and_copy()