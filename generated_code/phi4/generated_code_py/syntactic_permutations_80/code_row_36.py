import sys

def scan():
    input_data = sys.stdin.read(1023)  # Read up to 1023 characters plus one for potential newline
    if len(input_data) == 1023 and input_data[-1] != '\n':
        print("Error: Input exceeds buffer size.", file=sys.stderr)
    
    return len(input_data.rstrip('\n'))

# Example usage:
if __name__ == "__main__":
    sys.stdin = open('input.txt', 'r')  # For testing, replace this line with actual input redirection
    num_chars_read = scan()
    print(f"Number of characters read: {num_chars_read}")