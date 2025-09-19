import sys

def main():
    if len(sys.argv) != 2:
        print("Error: Please provide exactly one argument.")
        return
    
    input_str = sys.argv[1]

    if not isinstance(input_str, str):
        print("Error: The provided argument is not a string.")
        return

    trimmed_str = ''.join(char for char in input_str.rstrip())
    
    final_string = ''.join(line.rstrip('\n') for line in trimmed_str.splitlines())

    null_terminated_string = final_string + '\0'

    print(null_terminated_string)

if __name__ == "__main__":
    main()