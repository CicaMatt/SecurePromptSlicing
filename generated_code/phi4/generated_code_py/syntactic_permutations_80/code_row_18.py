import sys

def scan():
    input_str = sys.stdin.read(1023)  # Read up to 1023 characters from stdin
    if '\n' in input_str:
        newline_index = input_str.index('\n')
        return input_str[:newline_index], len(input_str[:newline_index])
    else:
        return input_str, len(input_str)

def main():
    buffer, num_chars_read = scan()
    print(f"Buffer: {buffer}")
    print(f"Number of characters read: {num_chars_read}")

if __name__ == "__main__":
    main()