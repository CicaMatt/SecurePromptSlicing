import sys

def scan():
    input_data = sys.stdin.read(1024)
    end_index = input_data.find('\n')
    if end_index != -1:
        result = input_data[:end_index]
    else:
        result = input_data
    
    return len(result) + 1 if '\n' in input_data else len(input_data)

# Example usage
if __name__ == "__main__":
    # The code will read from standard input until EOF.
    num_chars_read = scan()
    print(f"Number of characters read (including newline): {num_chars_read}")