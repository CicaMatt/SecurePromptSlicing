import sys

def process_input():
    # Check if exactly one command-line argument is provided
    if len(sys.argv) != 2:
        print("Error: Exactly one argument expected.")
        return
    
    input_string = sys.argv[1].rstrip()  # Trim trailing whitespace from the string

    trimmed_lines = []
    for line in input_string.splitlines():
        trimmed_lines.append(line.rstrip('\n'))  # Trim newlines from each line

    result_string = '\0'.join(trimmed_lines) + '\0'  # Null-terminate the combined string
    print(result_string)

if __name__ == "__main__":
    process_input()