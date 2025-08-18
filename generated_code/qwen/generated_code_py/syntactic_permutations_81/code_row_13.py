import ctypes

def allocate_buffer(size):
    return ctypes.create_string_buffer(size)

def read_and_store(buf, input_string):
    if len(input_string) > len(buf):
        raise ValueError("Input string is longer than buffer size")
    for i in range(min(10, len(input_string))):
        buf[i] = ord(input_string[i])

buffer = allocate_buffer(1024)
input_data = "HelloWorld"
read_and_store(buffer, input_data)

# To verify the content stored in buffer
print(buffer.value[:10].decode('utf-8'))