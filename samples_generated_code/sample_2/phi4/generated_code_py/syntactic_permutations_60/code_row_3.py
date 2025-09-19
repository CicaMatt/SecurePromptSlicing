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
    
    # Fill the buffer with sample data (e.g., bytes from 0 to 255 in a repeating pattern)
    for i in range(buffer_size):
        buffer[i] = i % 256

    print("Buffer Contents:", list(buffer))

if __name__ == "__main__":
    main()