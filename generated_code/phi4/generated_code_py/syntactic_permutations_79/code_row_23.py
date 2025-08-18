import sys

def allocate_and_copy():
    # Allocate a large buffer for buf
    buf = bytearray(100)
    
    # Copy up to 100 characters from stdin into buf
    data = sys.stdin.read(100)
    buf[:len(data)] = data.encode('utf-8')
    
    # Allocate another large buffer for buf1
    buf1 = bytearray(100)
    
    # Copy up to 100 characters from stdin into buf1
    data = sys.stdin.read(100)
    buf1[:len(data)] = data.encode('utf-8')

def main():
    allocate_and_copy()

if __name__ == '__main__':
    main()