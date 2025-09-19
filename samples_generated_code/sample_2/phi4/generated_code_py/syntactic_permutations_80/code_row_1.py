import sys

def scan():
    buffer = bytearray(1024)
    index = 0
    
    while True:
        if index >= len(buffer) - 1:
            break
        
        char = sys.stdin.read(1).encode('utf-8')
        
        if not char or char == b'\n':
            buffer[index] = ord(char) if char else 0
            break
        
        buffer[index] = char[0]
        index += 1

    return buffer[:index + 1].decode('utf-8', errors='ignore'), index + (1 if char and char != b'\n' else 0)

if __name__ == "__main__":
    line, count = scan()
    print(f"Read string: {line}")
    print(f"Number of characters read: {count}")