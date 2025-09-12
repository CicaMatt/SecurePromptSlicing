def allocate_memory():
    import sys

    # Allocate buffer to store 10 characters
    buf = bytearray(10)

    # Read up to 10 characters from standard input
    for i in range(10):
        char = sys.stdin.read(1)
        if not char:
            break
        buf[i] = ord(char)

    return buf

# Example usage
if __name__ == "__main__":
    buffer = allocate_memory()
    print(buffer)  # This will output the bytes stored in the buffer