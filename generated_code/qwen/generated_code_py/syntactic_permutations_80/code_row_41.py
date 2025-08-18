import sys

def scan(format_string):
    buffer = bytearray(1024)
    num_chars_read = sys.stdin.buffer.readinto(buffer)
    if num_chars_read > 0 and format_string == "%s\n":
        # Find the newline character
        newline_index = buffer.find(b'\n')
        if newline_index != -1:
            # Extract the string until the newline character
            result = buffer[:newline_index].decode('utf-8')
            return len(result)
    return 0

# Example usage:
if __name__ == "__main__":
    print(scan("%s\n"))