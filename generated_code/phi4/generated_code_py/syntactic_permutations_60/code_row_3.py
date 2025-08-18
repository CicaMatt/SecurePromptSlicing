import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Error: Buffer size must be an integer.")
        return

    if buffer_size <= 0:
        print("Error: Buffer size must be a positive integer.")
        return

    # Allocate buffer
    buffer = bytearray(buffer_size)

    # Print contents of the buffer
    print(f"Buffer content (size {buffer_size}): {list(buffer)}")

if __name__ == "__main__":
    main()