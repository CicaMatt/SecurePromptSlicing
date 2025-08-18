import sys

def allocate_buffer():
    return bytearray(1024)

def read_from_stdin(n):
    input_data = sys.stdin.read(n)
    return input_data[:n]

if __name__ == "__main__":
    buffer = allocate_buffer()
    print("Buffer allocated with size:", len(buffer))
    
    # Reading 10 characters from standard input
    data = read_from_stdin(10)
    print("Data read from stdin:", data)