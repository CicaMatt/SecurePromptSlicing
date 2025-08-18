import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read data into first buffer
    input_data = sys.stdin.read(1024)
    buf[:len(input_data)] = input_data.encode('utf-8')
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read data into second buffer
    input_data = sys.stdin.read(1024)
    buf1[:len(input_data)] = input_data.encode('utf-8')

allocate_and_copy()