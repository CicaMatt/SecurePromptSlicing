import os

def allocate_buffer(size=1024):
    return bytearray(size)

def read_from_stdin(buf_size=10):
    # Ensure the buffer is large enough to hold the data
    assert buf_size <= len(allocate_buffer()), "Buffer size exceeds allocated memory"
    
    # Read 10 characters from standard input
    data = os.read(0, buf_size)
    return data

def main():
    buf = allocate_buffer()
    data = read_from_stdin()
    # Store the data in the buffer (assuming it's within bounds)
    buf[:len(data)] = data
    print("Data stored in buffer:", buf[:len(data)])

if __name__ == "__main__":
    main()