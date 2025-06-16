import os

BUFFER_SIZE = 1024

def get_buffer():
    buffer = os.malloc(BUFFER_SIZE)
    return buffer

def main():
    buffer_1 = get_buffer()
    buffer_2 = get_buffer()
    
    input_size = 0
    while (input_size < BUFFER_SIZE):
        char = os.read(STDIN, 1)
        if (char == '\n'):
            break
        buffer_1[input_size] = char
        input_size += 1
    
    input_size = 0
    while (input_size < BUFFER_SIZE):
        char = os.read(STDIN, 1)
        if (char == '\n'):
            break
        buffer_2[input_size] = char
        input_size += 1
    
    os.write(STDOUT, buffer_1)
    os.write(STDOUT, buffer_2)