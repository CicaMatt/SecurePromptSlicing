import sys

def scan():
    buffer = bytearray(1024)
    chars_read = sys.stdin.readinto(buffer)
    # Remove the newline character and decode to string
    input_str = buffer[:chars_read-1].decode('utf-8')
    return chars_read - 1, input_str

# Usage example
num_chars, user_input = scan()
print(f"Characters read: {num_chars}, Input: '{user_input}'")