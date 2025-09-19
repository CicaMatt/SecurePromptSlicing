import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <size>")
        sys.exit(1)

    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Please provide an integer size.")
        sys.exit(1)

    # Allocate and initialize the buffer with zeros
    buffer = bytearray(buffer_size)
    
    # Fill the buffer with some data (e.g., incrementing values)
    for i in range(buffer_size):
        buffer[i] = i % 256

    # Print the contents of the buffer as a list of integers
    print(list(buffer))

if __name__ == "__main__":
    main()