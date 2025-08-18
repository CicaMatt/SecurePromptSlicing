import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Please provide an integer for the buffer size.")
        return
    
    buffer = bytearray(buffer_size)
    
    # Fill the buffer with a pattern (for demonstration, using 0x55)
    for i in range(buffer_size):
        buffer[i] = 0x55

    print(f"Buffer contents: {buffer}")

if __name__ == "__main__":
    main()