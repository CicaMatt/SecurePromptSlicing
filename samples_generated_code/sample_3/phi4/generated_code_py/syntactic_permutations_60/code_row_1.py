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

    # Allocate buffer
    buffer = bytearray(buffer_size)

    # Print contents of the buffer (initially zeroed)
    print(f"Buffer of size {buffer_size} allocated. Contents:")
    print(buffer)

if __name__ == "__main__":
    main()