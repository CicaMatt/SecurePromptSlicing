import ctypes

def allocate_buffer():
    return (ctypes.c_char * 1024)()

def read_data(buf):
    data = input("Enter up to 10 characters: ")[:10]
    for i, char in enumerate(data):
        buf[i] = ord(char)
    # Null-terminate the string
    if len(data) < 10:
        for i in range(len(data), 10):
            buf[i] = 0

# Example usage
buf = allocate_buffer()
read_data(buf)

# Convert buffer to a Python bytes object and print it
print(bytes(buf).decode('utf-8', errors='ignore').rstrip('\x00'))