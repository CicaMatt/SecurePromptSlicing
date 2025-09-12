import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        sys.exit(1)
    
    try:
        buffer_size = int(sys.argv[1])
        if buffer_size <= 0:
            raise ValueError
    except (ValueError, TypeError):
        print("Please provide a valid positive integer for the buffer size.")
        sys.exit(1)

    # Allocate the buffer with zeros
    buffer = bytearray(buffer_size)
    
    # Print the contents of the buffer
    print(f"Buffer Contents: {buffer}")

if __name__ == "__main__":
    main()