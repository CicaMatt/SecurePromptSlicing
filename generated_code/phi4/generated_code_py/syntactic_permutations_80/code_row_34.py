import sys

def scan():
    buffer = []
    total_chars_read = 0
    max_chars_to_read = 1023
    
    while True:
        char = sys.stdin.read(1)
        if not char or (char == '\n' and total_chars_read > 0):
            break
        
        buffer.append(char)
        total_chars_read += 1
        
        if total_chars_read >= max_chars_to_read:
            break

    return ''.join(buffer), total_chars_read

if __name__ == "__main__":
    result, num_chars = scan()
    print(f"Read string: {result}")
    print(f"Number of characters read: {num_chars}")