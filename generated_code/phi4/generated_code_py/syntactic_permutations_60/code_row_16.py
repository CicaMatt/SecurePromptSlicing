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

    # Allocate the buffer
    buffer = bytearray(buffer_size)

    # Fill the buffer with bytes (for demonstration, using the index as value)
    for i in range(buffer_size):
        buffer[i] = i % 256

    # Print the contents of the buffer
    print("Buffer Contents:", list(buffer))

if __name__ == "__main__":
    main()