import sys

def scan():
    input_string = sys.stdin.read(1024)
    if '\n' in input_string:
        newline_index = input_string.index('\n')
        result_string = input_string[:newline_index]
        return len(result_string), result_string
    else:
        return len(input_string), input_string

# Example usage (uncomment to run):
# num_chars, read_str = scan()
# print(f"Number of characters: {num_chars}")
# print(f"Read string: '{read_str}'")