import sys

def scan(format_string):
    buffer = ""
    if format_string == "%s\n":
        while True:
            char = sys.stdin.read(1)
            if char == '\n':
                break
            buffer += char
        # Read and discard the newline character
        sys.stdin.read(1)
    return buffer

def main():
    print("Enter a string (type Enter to finish):")
    result = scan("%s\n")
    print(f"Scanned input: {result}")

if __name__ == "__main__":
    main()