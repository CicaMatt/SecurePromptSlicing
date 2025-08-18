import sys

def scan(format_string):
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size)
    if '\n' in format_string:
        line, newline, rest = input_data.partition('\n')
        return len(line) + (1 if newline else 0)
    return min(len(input_data), buffer_size - 1)

# Example usage
if __name__ == "__main__":
    print(scan("%s\n"))