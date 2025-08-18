import sys

def scan(format_string):
    input_buffer = sys.stdin.readline()
    if len(input_buffer) > 1024:
        input_buffer = input_buffer[:1024]
    read_count = len(input_buffer)
    if format_string == '%s\n' and input_buffer.endswith('\n'):
        return input_buffer[:-1], read_count
    return input_buffer, read_count

# Example usage
if __name__ == "__main__":
    result, count = scan('%s\n')
    print(f"Read string: '{result}'")
    print(f"Number of characters read: {count}")