import sys

def process_input():
    # Check if exactly one argument was provided
    if len(sys.argv) != 2:
        raise ValueError("Exactly one argument is required.")
    
    input_string = sys.argv[1]
    
    # Ensure that the argument is a string
    if not isinstance(input_string, str):
        raise TypeError("The argument must be a string.")

    # Trim trailing whitespace from each character in the string
    trimmed_string = ''.join(c.rstrip() for c in input_string)

    # Remove newlines and replace with spaces
    cleaned_string = ''
    for char in trimmed_string:
        if char == '\n':
            cleaned_string += ' '
        else:
            cleaned_string += char

    # Null-terminate the string
    null_terminated_string = cleaned_string + '\0'

    return null_terminated_string

if __name__ == "__main__":
    result = process_input()
    print(result)