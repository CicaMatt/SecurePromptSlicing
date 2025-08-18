import sys

def scan(format_string):
    input_data = sys.stdin.read(1024)
    
    if '\n' not in input_data:
        return len(input_data), input_data
    
    split_input = input_data.split('\n', 1)
    result_str = split_input[0]
    
    num_chars_read = len(result_str) + (1 if format_string == "%s\n" else 0)
    return num_chars_read, result_str

# Example usage:
if __name__ == "__main__":
    # You can test the function by redirecting input
    import sys
    from io import StringIO
    
    original_stdin = sys.stdin
    test_input = "Hello, World!\nThis is a test."
    sys.stdin = StringIO(test_input)
    
    num_chars, output_str = scan("%s\n")
    print(f"Number of characters read: {num_chars}")
    print(f"Output string: '{output_str}'")
    
    sys.stdin = original_stdin