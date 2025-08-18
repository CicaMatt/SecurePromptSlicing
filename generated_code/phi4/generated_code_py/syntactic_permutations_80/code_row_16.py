import sys

def scan(format_string):
    buffer = []
    char_count = 0
    
    input_stream = sys.stdin.read()
    
    if format_string == "%s\n":
        for i, char in enumerate(input_stream):
            if char_count < 1023:
                buffer.append(char)
                char_count += 1
            else:
                break
            if char == '\n':
                break
    
    return ''.join(buffer), char_count

# Example usage:
if __name__ == "__main__":
    import sys
    from io import StringIO
    
    # Simulating standard input for demonstration purposes.
    test_input = "Hello, World!\n"
    sys.stdin = StringIO(test_input)
    
    result_string, num_chars_read = scan("%s\n")
    print(f"Read string: {result_string}")
    print(f"Number of characters read: {num_chars_read}")