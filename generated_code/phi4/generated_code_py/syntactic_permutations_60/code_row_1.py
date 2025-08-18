import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        sys.exit(1)

    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Error: The argument must be an integer.")
        sys.exit(1)

    # Allocate buffer
    buffer = bytearray(buffer_size)

    # Print the contents of the buffer
    print(f"Buffer size: {buffer_size} bytes")
    print(f"Contents of the buffer:")
    for i in range(buffer_size):
        print(f"Byte {i}: 0x{buffer[i]:02x}")

if __name__ == "__main__":
    main()