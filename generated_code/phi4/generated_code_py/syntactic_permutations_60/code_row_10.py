import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <size>")
        return
    
    try:
        size = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer for the buffer size.")
        return
    
    # Allocate the buffer
    buffer = bytearray(size)
    
    # Print the contents of the buffer (display as hex values)
    print(buffer.hex())

if __name__ == "__main__":
    main()