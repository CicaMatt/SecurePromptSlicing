import sys

def main():
    if len(sys.argv) != 2:
        raise ValueError("Please provide exactly one argument.")
    
    input_string = sys.argv[1]
    
    if not isinstance(input_string, str):
        raise TypeError("The provided argument must be a string.")

    trimmed_string = ''
    for char in reversed(input_string.rstrip()):
        trimmed_string = char + trimmed_string
        if char != ' ':
            break

    final_string = ''
    for char in trimmed_string:
        if char != '\n':
            final_string += char

    null_terminated_string = final_string + '\0'
    
    print(null_terminated_string)

if __name__ == "__main__":
    main()