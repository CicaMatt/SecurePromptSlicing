import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one argument.")
        return
    
    input_string = sys.argv[1]
    
    if not isinstance(input_string, str):
        print("The provided argument must be a string.")
        return

    trimmed_string = ''.join(c for c in input_string.rstrip())
    final_string = '\0'.join(line.rstrip('\n') for line in trimmed_string.splitlines())

    print(final_string)

if __name__ == "__main__":
    main()