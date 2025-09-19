import sys

def scan(format_string):
    if format_string != "%s\n":
        raise ValueError("Unsupported format string. Only %s\\n is supported.")

    # Read from standard input up to 1023 characters plus the newline character
    input_data = sys.stdin.read(1024)
    
    # Find the position of the first newline character, if it exists
    newline_pos = input_data.find('\n')

    # If no newline is found and we've read more than 1023 bytes (due to reading up to 1024),
    # then raise an error because this means we have exceeded our limit without a proper end.
    if newline_pos == -1:
        if len(input_data) > 1023:
            raise ValueError("Input exceeds buffer size without a newline.")
        return input_data

    # Return the substring up to but not including the newline character
    result = input_data[:newline_pos]
    
    # Number of characters read is from start till just before newline
    num_chars_read = len(result)
    
    # Consume the newline character by reading it (it's already in input_data, so no need for additional reads)
    sys.stdin.read(1)

    return result, num_chars_read

# Example usage:
if __name__ == "__main__":
    try:
        result, count = scan("%s\n")
        print(f"Read string: {result}")
        print(f"Number of characters read: {count}")
    except Exception as e:
        print(e)