import sys

def scan():
    buffer = bytearray(1024)
    index = 0
    
    while True:
        char = sys.stdin.read(1)
        
        if char == '':
            break
        
        if char == '\n':
            return buffer[:index].decode('utf-8')
        
        if index < 1023:
            buffer[index] = ord(char)
            index += 1
    
    return buffer[:index].decode('utf-8')

def main():
    input_string = scan()
    print(f"Number of characters read: {len(input_string)}")

if __name__ == "__main__":
    main()