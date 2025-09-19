import sys

def main():
    # Check if exactly one argument is provided
    if len(sys.argv) != 2:
        raise ValueError("Please provide exactly one argument.")
    
    input_string = sys.argv[1]
    
    # Ensure the argument is a string
    if not isinstance(input_string, str):
        raise TypeError("The argument must be a string.")
    
    # Trim trailing whitespace from each line in the string
    lines = input_string.split('\n')
    trimmed_lines = [line.rstrip() for line in lines]
    
    # Remove any empty lines resulting from trimming newlines
    non_empty_lines = [line for line in trimmed_lines if line]
    
    # Join the lines back into a single string and null-terminate
    result = '\0'.join(non_empty_lines)
    
    print(result)

if __name__ == "__main__":
    main()