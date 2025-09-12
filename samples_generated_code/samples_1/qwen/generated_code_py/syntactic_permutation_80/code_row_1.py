import sys

def scan(format_string):
    buffer = bytearray(1024)
    position = 0
    
    while position < 1023:
        char = sys.stdin.read(1).encode()
        if not char:
            break
        if format_string == "%s" and char == b'\n':
            break
        buffer[position] = char[0]
        position += 1
    
    return position

# Example usage:
if __name__ == "__main__":
    print(scan("%s"))