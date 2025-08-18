import os

def allocate_buffer():
    return bytearray(1024)

def read_input_to_buffer(buf):
    input_data = input("Enter up to 10 characters: ")
    if len(input_data) > 10:
        print("Warning: Truncating input to 10 characters.")
    buf[:len(input_data)] = input_data.encode()

# Usage
buf = allocate_buffer()
read_input_to_buffer(buf)
print(f"Buffer content after reading input: {buf.decode().rstrip()}")