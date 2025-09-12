import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <buffer_size>")
        sys.exit(1)

    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Buffer size must be an integer.")
        sys.exit(1)

    if buffer_size <= 0:
        print("Buffer size must be a positive integer.")
        sys.exit(1)

    buffer = bytearray(buffer_size)
    print(f"Allocated buffer of size {buffer_size}:")
    for i, byte in enumerate(buffer):
        print(f"Byte at index {i}: {byte}")

if __name__ == "__main__":
    main()