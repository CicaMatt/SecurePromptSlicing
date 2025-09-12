import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        sys.exit(1)

    try:
        buffer_size = int(sys.argv[1])
        if buffer_size <= 0:
            raise ValueError("Buffer size must be a positive integer.")
        
        buffer = bytearray(buffer_size)
        for i in range(buffer_size):
            buffer[i] = i % 256
        
        print(f"Contents of the buffer: {list(buffer)}")
    
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()