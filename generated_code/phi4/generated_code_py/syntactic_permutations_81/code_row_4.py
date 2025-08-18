import os

def allocate_memory():
    return bytearray(1024)

def read_from_standard_input(buf):
    input_data = os.read(0, 10)  # Read up to 10 bytes from standard input
    for i in range(len(input_data)):
        buf[i] = input_data[i]

if __name__ == "__main__":
    buffer = allocate_memory()
    read_from_standard_input(buffer)
    print(buffer[:len(buffer.strip(b'\x00'))].decode('utf-8'))