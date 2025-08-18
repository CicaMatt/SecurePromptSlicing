import sys

def scan():
    input_buffer = []
    total_chars_read = 0
    
    while True:
        char = sys.stdin.read(1)
        
        if not char or char == '\n':
            break
        
        input_buffer.append(char)
        total_chars_read += 1
        
        if total_chars_read >= 1023:
            break
            
    return ''.join(input_buffer), total_chars_read

def main():
    scanned_string, num_chars = scan()
    print(f"Scanned String: {scanned_string}")
    print(f"Number of Characters Read: {num_chars}")

if __name__ == "__main__":
    main()