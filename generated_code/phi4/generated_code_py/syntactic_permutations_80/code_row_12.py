import sys

def scan():
    buffer = []
    max_chars = 1023
    
    while True:
        char = sys.stdin.read(1)
        if not char or char == '\n':
            break
        buffer.append(char)
        
        if len(buffer) >= max_chars:
            break
            
    result = ''.join(buffer)
    return len(result), result

if __name__ == "__main__":
    num_read, content = scan()
    print(f"Number of characters read: {num_read}")
    print(f"Content: {content}")