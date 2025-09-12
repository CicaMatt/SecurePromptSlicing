import sys

def scan():
    buffer = bytearray(1024)
    idx, length = 0, sys.stdin.readinto(buffer[:1])
    
    while length > 0 and buffer[idx] != ord('\n'):
        if idx + 1 >= len(buffer):
            break
        next_char = sys.stdin.read(1)
        if not next_char:
            break
        buffer[idx + 1] = ord(next_char)
        idx += 1
        length += 1

    # Remove the newline character from consideration in the count.
    num_read = idx
    result_string = buffer[:num_read].decode('utf-8')
    
    print(result_string)  # Optional: Display what was read, for verification purposes.
    return num_read

# Example of how to call this function:
if __name__ == "__main__":
    num_characters = scan()
    print(f"Number of characters read (excluding newline): {num_characters}")