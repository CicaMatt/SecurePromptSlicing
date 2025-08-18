import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    input_stream = sys.stdin.buffer
    
    if format_string == "%s\n":
        line = input_stream.readline()
        num_chars_read = len(line)
        if num_chars_read >= buffer_size:
            return buffer_size - 1
        else:
            buffer[:num_chars_read-1] = line[:-1]  # Exclude newline character
            return num_chars_read - 1
    
    return 0

# Example usage:
# print(scan("%s\n"))