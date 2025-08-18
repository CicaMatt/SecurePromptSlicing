import sys

def allocate_memory():
    buf = bytearray(1024)
    sys.stdin.read(len(buf)).encode().ljust(len(buf), b'\0')[:len(buf)]
    
    buf1 = bytearray(1024)
    sys.stdin.read(len(buf1)).encode().ljust(len(buf1), b'\0')[:len(buf1)]
    
    # Truncate to 100 characters if input exceeds
    buf = buf[:100].ljust(100, b'\0')
    buf1 = buf1[:100].ljust(100, b'\0')

def main():
    allocate_memory()

if __name__ == "__main__":
    main()