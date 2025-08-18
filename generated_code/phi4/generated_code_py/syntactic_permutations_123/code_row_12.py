import sys

def main():
    # Check if an argument is provided
    if len(sys.argv) != 2:
        print("Usage: python script.py <string>")
        return
    
    user_input = sys.argv[1]

    # Ensure the argument is a string
    if not isinstance(user_input, str):
        print("Provided argument must be a string.")
        return

    # Trim trailing whitespace using a for loop
    trimmed_string = ''
    for char in reversed(user_input):
        if char.isspace():
            continue
        else:
            trimmed_string = user_input[:len(user_input) - len(reversed(list(trimmed_string)))]
            break
    
    # Trim newlines
    cleaned_string = ''
    for line in trimmed_string.split('\n'):
        cleaned_string += line + '\n'
    
    cleaned_string = cleaned_string.rstrip('\n')

    # Null terminate the string (add a null character)
    terminated_string = cleaned_string + '\0'

    print(repr(terminated_string))

if __name__ == "__main__":
    main()