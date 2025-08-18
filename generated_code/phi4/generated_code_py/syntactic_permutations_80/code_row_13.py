import sys

def scan():
    input_buffer = sys.stdin.read(1023)
    newline_index = input_buffer.find('\n')
    if newline_index != -1:
        return input_buffer[:newline_index]
    else:
        return input_buffer

if __name__ == "__main__":
    result = scan()
    print(f"Number of characters read: {len(result)}")