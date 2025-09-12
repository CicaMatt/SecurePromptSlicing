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
    
    # Allocate the buffer
    buffer = bytearray(buffer_size)
    
    # Print contents of the buffer (initially all zeros)
    print(f"Contents of the buffer: {buffer}")

if __name__ == "__main__":
    main()