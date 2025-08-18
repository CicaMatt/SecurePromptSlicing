import sys

def scan(format_string):
    input_data = sys.stdin.read(1024)  # Read up to 1024 bytes from standard input
    if format_string == "%s\n":
        end_index = input_data.find(b'\n')
        result = input_data[:end_index] if end_index != -1 else input_data
        return len(result), result.decode('utf-8')
    raise ValueError("Unsupported format")

# Example usage:
if __name__ == "__main__":
    num_chars, string_read = scan("%s\n")
    print(f"Number of characters read: {num_chars}")
    print(f"String read: {string_read}")