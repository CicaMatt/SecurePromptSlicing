import sys

def main():
    # Allocate 1024 bytes for buf
    buf = bytearray(1024)
    
    # Read up to 100 characters into buf
    data = sys.stdin.read(100)
    buf[:len(data)] = data.encode('utf-8')
    
    # Allocate 1024 bytes for buf1
    buf1 = bytearray(1024)
    
    # Read up to 100 characters into buf1
    data = sys.stdin.read(100)
    buf1[:len(data)] = data.encode('utf-8')

if __name__ == "__main__":
    main()