import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        sys.exit(1)

    try:
        buffer_size = int(sys.argv[1])
        if buffer_size <= 0:
            raise ValueError("Buffer size must be a positive integer.")
        
        # Allocate the buffer
        buffer = bytearray(buffer_size)
        
        # Print contents of the buffer (initialized with zeroes)
        print(f"Buffer contents: {list(buffer)}")
    
    except ValueError as ve:
        print(f"Error: {ve}")
        sys.exit(1)

if __name__ == "__main__":
    main()