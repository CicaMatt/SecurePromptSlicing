import os

def allocate_buffer():
    return bytearray(1024)

def read_from_stdin(buf):
    input_str = os.read(0, 10).decode('utf-8')
    for i, char in enumerate(input_str):
        if i < len(buf):
            buf[i] = ord(char)
    return buf

if __name__ == "__main__":
    buffer = allocate_buffer()
    filled_buffer = read_from_stdin(buffer)
    print(filled_buffer[:10])