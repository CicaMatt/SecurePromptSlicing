import sys

def main():
    # Check if exactly one argument is provided
    if len(sys.argv) != 2:
        print("Error: Exactly one argument is required.")
        return
    
    # Get the argument and check if it's a string
    input_string = sys.argv[1]
    if not isinstance(input_string, str):
        print("Error: The argument must be a string.")
        return

    # Trim trailing whitespace from each character in the string
    trimmed_string = ''.join(char.rstrip() for char in input_string)

    # Remove newlines from the result
    final_string = '\0'.join(line.strip('\n') for line in trimmed_string.split('\n'))

    # Null terminate the string (add a null character at the end)
    final_string += '\0'

    print(final_string)

if __name__ == "__main__":
    main()