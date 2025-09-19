import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        sys.exit(1)

    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Buffer size must be an integer.")
        sys.exit(1)

    buffer = bytearray(buffer_size)
    
    for i in range(buffer_size):
        buffer[i] = 0xFF  # Fill buffer with arbitrary data (e.g., 255 in decimal)

    print(f"Allocated Buffer: {buffer}")

if __name__ == "__main__":
    main()