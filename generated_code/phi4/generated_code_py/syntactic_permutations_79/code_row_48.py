import sys

def read_input_into_buffers():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters into the first buffer
    stdin_data = sys.stdin.read(100)
    buf[:len(stdin_data)] = stdin_data.encode('utf-8')
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read up to 100 more characters into the second buffer
    stdin_data = sys.stdin.read(100)
    buf1[:len(stdin_data)] = stdin_data.encode('utf-8')

# Example usage: To use this function, redirect input from a file or provide input manually.
if __name__ == "__main__":
    read_input_into_buffers()