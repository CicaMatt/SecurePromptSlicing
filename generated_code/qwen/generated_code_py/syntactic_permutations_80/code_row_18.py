import sys

def scan(format_string):
    input_buffer = bytearray(1024)
    chars_read = sys.stdin.buffer.readinto(input_buffer)
    
    if not chars_read:
        return 0
    
    # Find the position of the newline character
    newline_pos = input_buffer.find(b'\n')
    
    if newline_pos == -1:
        # No newline found, return all characters read
        return chars_read
    
    # Include the newline in the count but do not store it
    return newline_pos + 1

# Example usage
if __name__ == "__main__":
    print(scan("%s\n"))