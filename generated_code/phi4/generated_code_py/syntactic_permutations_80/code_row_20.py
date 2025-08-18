import sys

def scan():
    input_stream = sys.stdin.read(1024).split('\n', 1)
    if len(input_stream) < 2:
        return input_stream[0], len(input_stream[0])
    line, _ = input_stream
    return line, len(line)

# Example usage (uncomment the following lines to test):
# if __name__ == "__main__":
#     buffer, count = scan()
#     print(f"Read {count} characters: {buffer}")