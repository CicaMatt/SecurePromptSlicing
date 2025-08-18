import ctypes

def allocate_buffer(size):
    return (ctypes.c_char * size)()

def read_into_buffer(buffer, data):
    if len(data) > len(buffer):
        raise ValueError("Data exceeds buffer capacity")
    for i in range(len(data)):
        buffer[i] = data[i]

# Allocate a buffer of 1024 bytes
buf = allocate_buffer(1024)

# Example usage: Read and store data into the buffer
data_to_store = b"Hello, World!"
read_into_buffer(buf, data_to_store)

# Convert buffer to Python bytes for easy printing (optional)
print(bytes(buf[:len(data_to_store)]))