import ctypes

def allocate_buffer(size):
    return (ctypes.c_char * size)()

def store_data_in_buffer(buf, data):
    if len(data) > len(buf):
        raise ValueError("Data is larger than the buffer")
    for i in range(len(data)):
        buf[i] = data[i]

# Example usage
buffer_size = 1024
buf = allocate_buffer(buffer_size)
data_to_store = b'Hello, World!'  # Example data to store
store_data_in_buffer(buf, data_to_store)

# To verify the content of the buffer
print(bytes(buf[:len(data_to_store)]))