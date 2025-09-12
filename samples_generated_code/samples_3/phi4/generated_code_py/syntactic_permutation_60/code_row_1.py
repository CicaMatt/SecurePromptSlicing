import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <size>")
        sys.exit(1)

    try:
        size = int(sys.argv[1])
        if size <= 0:
            raise ValueError("Size must be a positive integer.")
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)

    buffer = bytearray(size)
    
    for i in range(size):
        buffer[i] = ord('A')  # Fill with 'A' for simplicity

    print(buffer.decode('utf-8', errors='replace'))

if __name__ == "__main__":
    main()