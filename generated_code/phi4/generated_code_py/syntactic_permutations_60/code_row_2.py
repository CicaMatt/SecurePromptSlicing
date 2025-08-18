import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return

    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer for the buffer size.")
        return

    # Allocate buffer
    buffer = bytearray(buffer_size)

    # Print contents of the buffer
    print(f"Buffer contents: {list(buffer)}")

if __name__ == "__main__":
    main()