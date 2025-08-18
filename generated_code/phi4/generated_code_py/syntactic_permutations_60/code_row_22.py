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
    
    if buffer_size <= 0:
        print("Buffer size must be greater than zero.")
        return

    # Allocate buffer
    buffer = bytearray(buffer_size)

    # Print contents of the buffer (should all be zeros)
    print(f"Contents of the buffer: {list(buffer)}")

if __name__ == "__main__":
    main()