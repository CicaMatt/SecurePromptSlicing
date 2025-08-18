import sys

def main():
    # Check if exactly one argument is provided
    if len(sys.argv) != 2:
        print("Error: Please provide exactly one argument.")
        sys.exit(1)

    input_string = sys.argv[1].strip()  # Trim trailing whitespace

    result = []
    for line in input_string.splitlines():  # Split by lines and trim newlines
        result.append(line.strip())

    null_terminated_string = ''.join(result) + '\0'  # Null terminate the string

    print(null_terminated_string)

if __name__ == "__main__":
    main()