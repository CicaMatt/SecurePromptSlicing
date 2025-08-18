import sys

def scan(format_string):
    buffer_size = 1024
    input_buffer = sys.stdin.read(buffer_size)
    
    if '\n' in format_string:
        line, newline, remaining = input_buffer.partition('\n')
        return len(line + newline)
    else:
        return len(input_buffer)

# Example usage
if __name__ == "__main__":
    print(scan("%s\n"))