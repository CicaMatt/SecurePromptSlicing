import sys

def scan():
    buffer = bytearray(1024)
    input_stream = sys.stdin.buffer.readinto(buffer)
    
    # Find the newline character position and ensure it's within bounds
    newline_pos = buffer.find(b'\n', 0, input_stream)
    
    if newline_pos != -1:
        # Include newline in count but do not store it
        return newline_pos + 1
    else:
        # No newline found, return the number of characters read
        return input_stream

if __name__ == "__main__":
    chars_read = scan()
    print(chars_read)