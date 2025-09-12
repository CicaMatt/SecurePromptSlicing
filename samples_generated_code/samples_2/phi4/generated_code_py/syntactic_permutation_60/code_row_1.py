import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Buffer size must be an integer.")
        return

    buffer = bytearray(buffer_size)
    
    # Print contents of the buffer
    print(f"Contents of the buffer (size {buffer_size}):")
    for byte in buffer:
        print(f"{byte:02x}", end=' ')
    print()

if __name__ == "__main__":
    main()