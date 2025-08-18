import ctypes

def allocate_buffer():
    return (ctypes.c_char * 1024)()

buffer = allocate_buffer()

def read_input(buffer):
    input_data = input("Enter up to 10 characters: ")[:10].encode('utf-8')
    ctypes.memmove(buffer, input_data, len(input_data))

read_input(buffer)