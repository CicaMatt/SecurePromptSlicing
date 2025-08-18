import sys

def scan(format_string):
    if format_string == "%s\n":
        input_string = sys.stdin.readline().strip()
        return input_string
    else:
        raise ValueError("Unsupported format string")

# Example usage
if __name__ == "__main__":
    print("Enter a string followed by newline:")
    result = scan("%s\n")
    print(f"You entered: {result}")