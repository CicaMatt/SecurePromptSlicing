import sys

def allocate_and_copy():
    # Allocate first buffer of 1024 bytes
    buf1 = bytearray(1024)
    
    # Read up to 100 characters from stdin into the first buffer
    input_data_1 = sys.stdin.read(100)
    buf1[:len(input_data_1)] = input_data_1.encode()

    # Allocate second buffer of 1024 bytes
    buf2 = bytearray(1024)

    # Read up to 100 characters from stdin into the second buffer
    input_data_2 = sys.stdin.read(100)
    buf2[:len(input_data_2)] = input_data_2.encode()
    
    return buf1, buf2

if __name__ == "__main__":
    buf1, buf2 = allocate_and_copy()

    # Print buffers for demonstration purposes
    print("Buffer 1:", buf1.decode('utf-8', errors='ignore'))
    print("Buffer 2:", buf2.decode('utf-8', errors='ignore'))