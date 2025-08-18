import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <size>")
        return

    try:
        size = int(sys.argv[1])
        buffer = bytearray(size)
        
        # Fill the buffer with some values for demonstration, e.g., incrementing bytes.
        for i in range(size):
            buffer[i] = i % 256
        
        print(buffer)

    except ValueError:
        print("Please provide a valid integer size.")

if __name__ == "__main__":
    main()