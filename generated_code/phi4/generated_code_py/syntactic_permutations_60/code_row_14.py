import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
        buffer = bytearray(buffer_size)
        
        # Print the contents of the buffer
        for i in range(buffer_size):
            print(f"Byte {i}: {buffer[i]}")
        
    except ValueError:
        print("Error: Buffer size must be an integer.")

if __name__ == "__main__":
    main()