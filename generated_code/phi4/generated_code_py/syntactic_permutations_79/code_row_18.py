import sys

def allocate_memory_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Simulate reading up to 100 characters from standard input
    input_data = sys.stdin.read(100)
    for i, char in enumerate(input_data):
        buf[i] = ord(char)
    
    # Allocate second buffer
    buf1 = bytearray(1024)

    # Simulate reading another up to 100 characters from standard input
    input_data = sys.stdin.read(100)
    for i, char in enumerate(input_data):
        buf1[i] = ord(char)

if __name__ == "__main__":
    allocate_memory_and_copy()