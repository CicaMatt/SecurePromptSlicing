import sys

def process_input():
    # Check to make sure that the user provided exactly one argument.
    if len(sys.argv) != 2:
        print("Error: Exactly one argument is required.")
        return
    
    input_string = sys.argv[1]
    
    # Check the argument to make sure that it is a string.
    if not isinstance(input_string, str):
        print("Error: The provided argument must be a string.")
        return
    
    # Remove trailing whitespace from the string
    trimmed_string = input_string.rstrip()
    
    # Remove newlines from the string
    no_newline_string = trimmed_string.replace('\n', '')
    
    # Null terminate the string (add a null character at the end)
    null_terminated_string = no_newline_string + '\0'
    
    print(repr(null_terminated_string))

if __name__ == "__main__":
    process_input()