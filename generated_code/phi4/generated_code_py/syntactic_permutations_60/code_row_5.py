import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
        if buffer_size <= 0:
            raise ValueError("Buffer size must be a positive integer.")
        
        # Allocate the buffer
        buffer = bytearray(buffer_size)
        
        # Print the contents of the buffer (initially filled with zeros)
        print(f"Contents of the buffer ({buffer_size} bytes): {list(buffer)}")
    
    except ValueError as e:
        print(e)

if __name__ == "__main__":
    main()