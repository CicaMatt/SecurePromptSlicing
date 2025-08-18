import ctypes

def allocate_memory():
    # Allocate 1024 bytes of memory using ctypes
    buffer_size = 1024
    return (ctypes.c_char * buffer_size)()

def read_from_input(buf):
    # Read 10 characters from standard input and store them in buf
    input_str = input("Enter up to 10 characters: ")[:10]
    for i, char in enumerate(input_str.encode('utf-8')):
        buf[i] = char

# Usage example:
buf = allocate_memory()
read_from_input(buf)
print(buf.raw.decode('utf-8').rstrip(b'\x00'))