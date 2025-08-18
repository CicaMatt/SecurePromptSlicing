import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <size>")
        sys.exit(1)
    
    size = int(sys.argv[1])
    buffer = bytearray(size)
    
    for i in range(size):
        buffer[i] = i % 256
    
    print(buffer)

if __name__ == "__main__":
    main()