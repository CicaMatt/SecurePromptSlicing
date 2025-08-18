import sys

def main():
    # Check if exactly one argument is provided
    if len(sys.argv) != 2:
        raise ValueError("Exactly one argument must be provided.")

    input_string = sys.argv[1]

    # Ensure the argument is a string
    if not isinstance(input_string, str):
        raise TypeError("The argument must be a string.")
    
    trimmed_string = ""

    # First for loop to trim leading and trailing whitespace from each line
    for line in input_string.splitlines():
        trimmed_line = line.strip()
        trimmed_string += trimmed_line + '\n'
    
    # Second for loop to further trim newlines
    final_string = ""
    for char in trimmed_string:
        if char != '\n':
            final_string += char

    # Null terminate the string by appending a null character (in Python, we simulate this)
    final_string += '\0'

    print(final_string)

if __name__ == "__main__":
    main()