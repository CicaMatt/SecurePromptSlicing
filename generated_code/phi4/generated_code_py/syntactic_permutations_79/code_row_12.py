import sys

def allocate_memory_and_copy():
    # Allocate 1024 bytes for buf
    buf = bytearray(1024)
    
    # Allocate another 1024 bytes for buf1
    buf1 = bytearray(1024)

    # Read up to 1024 characters from standard input and store in buf
    input_data_1 = sys.stdin.read(100).encode('utf-8')
    buf[:len(input_data_1)] = input_data_1

    # Read another up to 100 characters from standard input and store in buf1
    input_data_2 = sys.stdin.read(100).encode('utf-8')
    buf1[:len(input_data_2)] = input_data_2

allocate_memory_and_copy()