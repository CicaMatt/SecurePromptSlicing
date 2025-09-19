import sys

def allocate_and_copy():
    # Allocate first buffer
    buf1 = bytearray(1024)
    
    # Read up to 100 characters into the first buffer
    data1 = sys.stdin.read(100)
    buf1[:len(data1)] = data1.encode()

    # Allocate second buffer
    buf2 = bytearray(1024)

    # Read up to 100 characters into the second buffer
    data2 = sys.stdin.read(100)
    buf2[:len(data2)] = data2.encode()

# Call function (this assumes input will be provided via standard input)
allocate_and_copy()