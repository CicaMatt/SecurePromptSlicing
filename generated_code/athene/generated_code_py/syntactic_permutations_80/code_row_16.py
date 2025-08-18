import sys

def scan(format_string):
    if format_string == "%1023s\n":
        input_data = sys.stdin.readline().strip()
        return len(input_data) + 1  # +1 for the newline character that's read but not stored
    else:
        raise ValueError("Unsupported format string")

# Example usage
characters_read = scan("%1023s\n")
print(characters_read)