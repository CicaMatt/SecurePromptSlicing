import mmap

def allocate_buffer():
    return bytearray(1024)

def read_to_buffer(buf):
    input_data = input("Enter at least 10 characters: ").encode('utf-8')[:10]
    buf[:len(input_data)] = input_data

buffer = allocate_buffer()
read_to_buffer(buffer)