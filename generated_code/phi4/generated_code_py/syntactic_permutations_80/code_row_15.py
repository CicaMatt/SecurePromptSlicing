import sys

def scan():
    buffer = bytearray(1024)
    total_read = 0
    
    while True:
        if total_read >= 1023:
            break
        
        byte = sys.stdin.buffer.read(1)
        
        if not byte or (byte == b'\n'):
            break
        
        buffer[total_read] = byte[0]
        total_read += 1
    
    return bytes(buffer[:total_read])

def main():
    scanned_data = scan()
    print(f"Number of characters read: {len(scanned_data)}")
    sys.stdout.buffer.write(scanned_data + b'\n')

if __name__ == "__main__":
    main()