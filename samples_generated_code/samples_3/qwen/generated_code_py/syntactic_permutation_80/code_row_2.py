import sys

def scan(format_string):
    if format_string != "%s\n":
        raise ValueError("Unsupported format string")
    
    input_buffer = []
    while True:
        char = sys.stdin.read(1)
        if not char or char == '\n':
            break
        input_buffer.append(char)
        if len(input_buffer) >= 1023:
            break
    
    return len(''.join(input_buffer))

# Example usage:
# To test this function, you can use the following code:
# import io
# sys.stdin = io.StringIO("Hello World\nThis is a test.")
# print(scan("%s\n"))  # Output: 11