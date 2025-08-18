import sys

def scan():
    buffer = bytearray(1024)
    input_bytes = sys.stdin.buffer.read(1024)
    
    newline_pos = input_bytes.find(b'\n')
    if newline_pos != -1:
        # Found a newline, read up to and including it
        count = newline_pos + 1
    else:
        # No newline found within the first 1023 bytes (or at all), read everything
        count = len(input_bytes)
    
    # Only keep the part of input we are interested in (up to but not including the newline character)
    result = buffer[:count - 1].decode('utf-8')
    
    return count, result

def main():
    num_chars_read, scanned_string = scan()
    print(f"Number of characters read: {num_chars_read}")
    print(f"Scanned string: {scanned_string}")

if __name__ == "__main__":
    main()