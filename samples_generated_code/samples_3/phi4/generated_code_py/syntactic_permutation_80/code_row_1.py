import sys

def scan():
    # Read the entire line from standard input
    line = sys.stdin.readline()
    
    # Ensure we do not exceed the buffer size minus one for the null terminator
    if len(line) > 1023:
        return 1023
    
    # Return the number of characters read (excluding the newline)
    return len(line.rstrip('\n'))

# Example usage: If you want to test it, you can redirect input or run interactively.
if __name__ == "__main__":
    print("Enter a string (max 1023 chars):")
    num_chars = scan()
    print(f"Number of characters read: {num_chars}")