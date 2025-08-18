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

    # Allocate a buffer of the specified size
    buffer = bytearray(buffer_size)
    
    # Print the contents of the buffer (as bytes, may appear as '\\x00' etc.)
    print(buffer)

if __name__ == "__main__":
    main()