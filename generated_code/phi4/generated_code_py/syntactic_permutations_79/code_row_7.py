import sys

def read_input():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters into buf
    input_data = sys.stdin.read(100)
    buf[:len(input_data)] = input_data.encode('utf-8')
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read up to another 100 characters into buf1
    input_data = sys.stdin.read(100)
    buf1[:len(input_data)] = input_data.encode('utf-8')

if __name__ == "__main__":
    read_input()