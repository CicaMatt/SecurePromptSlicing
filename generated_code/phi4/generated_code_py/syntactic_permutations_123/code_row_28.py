import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one argument.")
        return
    
    input_string = sys.argv[1]
    
    if not isinstance(input_string, str):
        print("The provided argument is not a string.")
        return

    trimmed_string = input_string.rstrip()
    
    result_string = ''
    for char in trimmed_string:
        if char != '\n':
            result_string += char
    
    # Null-terminate by adding a null character
    result_string += '\0'
    
    print(result_string)

if __name__ == "__main__":
    main()