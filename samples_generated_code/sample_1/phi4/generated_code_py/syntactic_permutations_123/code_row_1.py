import sys

def main():
    if len(sys.argv) != 2:
        print("Error: Exactly one argument is required.")
        return

    input_string = sys.argv[1]

    if not isinstance(input_string, str):
        print("Error: The argument must be a string.")
        return

    trimmed_string = ''.join(char for char in input_string.rstrip())

    final_string = ''.join(line.rstrip() for line in trimmed_string.splitlines())
    
    null_terminated_string = final_string + '\0'

    print(null_terminated_string)

if __name__ == "__main__":
    main()