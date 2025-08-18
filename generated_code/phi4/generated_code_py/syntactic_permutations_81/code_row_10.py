import ctypes

# Allocate a buffer of 1024 bytes
buf = (ctypes.c_char * 1024)()

def store_in_buf(data):
    if len(data.encode('utf-8')) > 1024:
        raise ValueError("Data exceeds buffer size")
    
    # Store data in the buffer
    for i, byte in enumerate(data.encode('utf-8')):
        buf[i] = byte

# Example usage:
try:
    store_in_buf("Hello, World!")
except ValueError as e:
    print(e)

# Print stored data from buffer
print(buf.raw[:buf.value.count(b'\x00')])