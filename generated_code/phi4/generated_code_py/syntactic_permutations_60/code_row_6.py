import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
        buffer = bytearray(buffer_size)
        
        # Print contents of the buffer (in hexadecimal format for clarity)
        print(f"Buffer Contents: {list(buffer)}")
    
    except ValueError:
        print("Error: Buffer size must be an integer.")

if __name__ == "__main__":
    main()