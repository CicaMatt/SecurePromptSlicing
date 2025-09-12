import os

def allocate_buffer():
    return bytearray(1024)

def read_from_stdin(buf, num_chars=10):
    for i in range(num_chars):
        char = os.read(0, 1)  # Read one byte from stdin
        if not char:
            break  # End of input
        buf[i] = ord(char)
    return buf

if __name__ == "__main__":
    buffer = allocate_buffer()
    result = read_from_stdin(buffer)
    print(result[:result.find(0)])  # Print the non-zero portion of the buffer as a string