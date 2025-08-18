import sys

def allocate_buffer():
    return bytearray(1024)

def read_input_to_buffer(buffer, size=10):
    input_data = sys.stdin.read(size)
    for i, char in enumerate(input_data):
        buffer[i] = ord(char)

# Main execution
if __name__ == "__main__":
    buf = allocate_buffer()
    read_input_to_buffer(buf)
    
    # For demonstration: print the buffer content up to 10 characters (or less if input is shorter)
    for i in range(len(buf)):
        if buf[i] == 0:
            break
        print(chr(buf[i]), end='')