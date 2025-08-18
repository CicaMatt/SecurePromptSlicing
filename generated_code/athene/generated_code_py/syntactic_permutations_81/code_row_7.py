import ctypes

def allocate_memory():
    return (ctypes.c_char * 1024)()

def read_input(buf):
    input_str = input()[:10]
    for i, char in enumerate(input_str.encode()):
        buf[i] = char

buf = allocate_memory()
read_input(buf)