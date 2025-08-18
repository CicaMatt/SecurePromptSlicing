import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
        if buffer_size <= 0:
            raise ValueError("Buffer size must be a positive integer.")
    except ValueError as e:
        print(f"Error: {e}")
        return

    # Allocate the buffer
    buffer = bytearray(buffer_size)
    
    # Print the contents of the buffer
    print(f"Buffer of size {buffer_size}:")
    for i in range(buffer_size):
        print(f"{i:03d}: {buffer[i]:02x}", end=' ')
        if (i + 1) % 16 == 0:
            print()
    print()

if __name__ == "__main__":
    main()