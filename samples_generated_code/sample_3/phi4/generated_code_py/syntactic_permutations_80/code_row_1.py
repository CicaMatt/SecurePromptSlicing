import sys

def custom_scan(format_string):
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size)
    
    # The format string indicates reading until a newline and consuming it
    if '\n' in input_data:
        # Split at the first newline
        parts = input_data.split('\n', 1)
        result = parts[0]
        
        # Number of characters read, excluding the newline itself
        num_chars_read = len(result)
        
        print(num_chars_read)
        return result

    # If no newline is found and we reached buffer size limit
    num_chars_read = len(input_data)
    print(num_chars_read)
    return input_data

# Example usage:
if __name__ == "__main__":
    line = custom_scan("%[^\n]%c")
    print(line)  # Output the line read from input, newline excluded