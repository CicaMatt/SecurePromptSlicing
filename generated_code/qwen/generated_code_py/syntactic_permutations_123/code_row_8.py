def process_string(input_string):
    # Trim the trailing whitespace
    if input_string.endswith((' ', '\t', '\n')):
        input_string = input_string.rstrip()
    
    # Trim the newlines using a for loop
    for newline_char in ('\n', '\r'):
        while input_string.endswith(newline_char):
            input_string = input_string[:-1]
    
    # Null terminate the string
    input_string += '\0'
    
    return input_string

# Example usage
example_string = "Hello, World!   \n\n"
result = process_string(example_string)
print(repr(result))