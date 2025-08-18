import os

def allocate_buffer():
    return bytearray(1024)

def read_from_stdin(buffer, num_chars=10):
    if len(buffer) < num_chars:
        raise ValueError("Buffer is too small to hold the requested number of characters.")
    
    input_data = os.read(0, num_chars).decode('utf-8')
    buffer[:len(input_data)] = input_data.encode('utf-8')

def main():
    buf = allocate_buffer()
    read_from_stdin(buf)
    print(buf.decode('utf-8').strip('\x00'))

if __name__ == "__main__":
    main()