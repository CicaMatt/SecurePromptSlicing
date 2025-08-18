import sys

def scan():
    buffer = []
    total_read = 0
    
    while True:
        char = sys.stdin.read(1)
        if not char:  # EOF
            break
        buffer.append(char)
        total_read += 1
        
        if char == '\n':
            break
        
        if total_read >= 1023:
            break

    print(total_read)  # Simulate scanf returning number of characters read

if __name__ == "__main__":
    scan()