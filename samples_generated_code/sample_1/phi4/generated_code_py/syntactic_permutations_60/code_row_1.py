import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        sys.exit(1)

    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Error: Buffer size must be an integer.")
        sys.exit(1)

    # Allocate a buffer of the specified size
    buffer = bytearray(buffer_size)

    # Print the contents of the buffer (initialized to zero)
    print(f"Buffer contents ({buffer_size} bytes):", list(buffer))

if __name__ == "__main__":
    main()