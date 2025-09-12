import os
import sys

def scan():
    # Define the maximum size for the input (1024 bytes)
    max_input_size = 1024
    
    # Use a fixed-size byte array to read input from stdin
    buffer = bytearray(max_input_size)

    # Read from standard input until newline or max input size is reached
    num_read_bytes = sys.stdin.readinto(buffer)
    
    if num_read_bytes == 0:
        return 0

    # Find the first occurrence of a newline character
    newline_index = buffer.find(b'\n')
    
    if newline_index != -1:
        # If newline is found, adjust the number of read bytes to exclude it
        num_read_chars = newline_index + 1
    else:
        # If no newline is found, use all bytes read as characters
        num_read_chars = num_read_bytes
    
    # Convert buffer (up to the first newline or end) into a string
    result_string = buffer[:num_read_chars - 1].decode('utf-8')
    
    print(result_string)
    return num_read_chars

if __name__ == "__main__":
    scan()