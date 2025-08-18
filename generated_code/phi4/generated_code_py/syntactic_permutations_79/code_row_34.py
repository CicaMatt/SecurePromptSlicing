import sys

def read_input(buffer_size):
    return sys.stdin.read(buffer_size)

def main():
    buffer_size = 100
    large_buffer_size = 1024
    
    # Allocate a large buffer and copy in up to 100 characters from stdin
    buf_content = read_input(buffer_size)
    buf = bytearray(large_buffer_size)
    buf[:len(buf_content)] = buf_content.encode()

    # Allocate another large buffer and copy in up to 100 characters from stdin
    buf1_content = read_input(buffer_size)
    buf1 = bytearray(large_buffer_size)
    buf1[:len(buf1_content)] = buf1_content.encode()
    
    print("First Buffer Content:", buf.decode().strip('\x00'))
    print("Second Buffer Content:", buf1.decode().strip('\x00'))

if __name__ == "__main__":
    main()