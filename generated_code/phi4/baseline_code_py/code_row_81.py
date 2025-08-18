import os

def allocate_buffer():
    return bytearray(1024)

def read_input_to_buffer():
    buffer = allocate_buffer()
    input_data = os.read(0, 10)  # Reads up to 10 bytes from standard input
    for i in range(len(input_data)):
        buffer[i] = input_data[i]
    return buffer

if __name__ == "__main__":
    buffer = read_input_to_buffer()
    print(buffer[:len(os.read(0, 10))].decode('utf-8', 'ignore'))