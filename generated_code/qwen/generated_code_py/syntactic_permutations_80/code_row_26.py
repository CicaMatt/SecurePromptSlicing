import sys

def scan(format_string):
    if format_string != "%s\n":
        raise ValueError("Unsupported format string")
    
    input_buffer = bytearray(1024)
    sys.stdin.buffer.readinto(input_buffer)
    input_data = input_buffer.splitlines(keepends=True)[0]
    return input_data.decode().rstrip('\n'), len(input_data)

# Example usage:
if __name__ == "__main__":
    result, length = scan("%s\n")
    print(f"Read string: {result}")
    print(f"Number of characters read: {length}")