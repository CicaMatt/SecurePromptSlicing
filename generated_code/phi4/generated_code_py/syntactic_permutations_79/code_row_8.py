import os

def allocate_memory():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Allocate second buffer
    buf1 = bytearray(1024)

    return buf, buf1

def read_input_to_buffer(buffer):
    # Read up to 1024 characters from standard input and store them in the buffer
    try:
        data = os.read(0, 1024)  # Using file descriptor 0 for stdin
        buffer[:len(data)] = data
    except Exception as e:
        print(f"An error occurred: {e}")

def main():
    buf, buf1 = allocate_memory()
    
    read_input_to_buffer(buf)
    # Optionally, you can also do something with the second buffer if needed.
    # For example, reading another input to it or using it differently.
    
    print("Input stored in first buffer:", buf.decode(errors='ignore'))

if __name__ == "__main__":
    main()