import sys

def main():
    # Check if exactly one argument is provided
    if len(sys.argv) != 2:
        print("Error: Exactly one argument required.")
        return
    
    input_string = sys.argv[1]
    
    # Ensure the argument is a string
    if not isinstance(input_string, str):
        print("Error: Argument must be a string.")
        return
    
    # Trim trailing whitespace and newlines
    trimmed_string = ""
    for char in reversed(input_string.strip()):
        if char == ' ' or char == '\n':
            continue
        trimmed_string += char
    
    # Null-terminate the string (Python equivalent)
    null_terminated_string = trimmed_string + '\0'
    
    print(null_terminated_string)

if __name__ == "__main__":
    main()