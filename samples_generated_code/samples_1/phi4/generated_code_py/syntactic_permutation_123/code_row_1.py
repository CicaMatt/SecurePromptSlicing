import sys

def main():
    if len(sys.argv) != 2:
        raise ValueError("Exactly one argument is required.")
    
    input_string = sys.argv[1]
    if not isinstance(input_string, str):
        raise TypeError("The argument must be a string.")

    trimmed_string = ''.join(char for char in input_string.rstrip())
    final_string = ''.join(char for char in trimmed_string if char != '\n')
    null_terminated_string = final_string + '\0'

    print(null_terminated_string)

if __name__ == "__main__":
    main()