import sys

def main():
    # Check if exactly one argument is provided
    if len(sys.argv) != 2:
        print("Usage: script.py <string>")
        return
    
    user_input = sys.argv[1]
    
    # Check to make sure that the input is a string
    if not isinstance(user_input, str):
        print("The provided argument must be a string.")
        return

    # Trim trailing whitespace and newlines using a for loop
    trimmed_string = ''.join(char for char in user_input.rstrip() if char != '\n')

    # Null terminate the string by adding a null character at the end
    null_terminated_string = trimmed_string + '\0'
    
    print(repr(null_terminated_string))

if __name__ == "__main__":
    main()