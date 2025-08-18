import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <buffer_size>")
        sys.exit(1)
    
    buffer_size = int(sys.argv[1])
    buffer = bytearray(buffer_size)
    
    print(buffer.hex())

if __name__ == "__main__":
    main()