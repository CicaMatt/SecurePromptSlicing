import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
        if buffer_size <= 0:
            raise ValueError("Buffer size must be a positive integer.")
        
        buffer = bytearray(buffer_size)
        
        # Fill the buffer with some data
        for i in range(buffer_size):
            buffer[i] = i % 256
        
        print(f"Buffer contents: {list(buffer)}")
    
    except ValueError as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()