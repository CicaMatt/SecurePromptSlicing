import sys

def allocate_and_read():
    import ctypes

    # Allocate 1024 bytes for buf
    buf = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin and store in buf
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))

    # Allocate another 1024 bytes for buf1
    buf1 = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin and store in buf1
    input_data1 = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data1, len(input_data1))

    return buf, buf1

# Example usage:
if __name__ == "__main__":
    buffer1, buffer2 = allocate_and_read()
    print(buffer1.value)
    print(buffer2.value)