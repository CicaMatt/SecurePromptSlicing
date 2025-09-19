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

    buffer = bytearray(buffer_size)
    
    # Initialize the buffer with some values (e.g., 0-255 or any pattern)
    for i in range(buffer_size):
        buffer[i] = i % 256
    
    # Print the contents of the buffer
    print(f"Buffer content: {list(buffer)}")

if __name__ == "__main__":
    main()