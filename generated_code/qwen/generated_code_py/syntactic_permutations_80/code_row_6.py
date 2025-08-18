import sys

def scan():
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    index = 0
    
    while index < buffer_size - 1:
        char = sys.stdin.read(1).encode()
        if not char:
            break
        if char == b'\n':
            break
        buffer[index] = char[0]
        index += 1
    
    return index

# Example usage
if __name__ == "__main__":
    print("Enter a string:")
    chars_read = scan()
    print(f"Number of characters read: {chars_read}")