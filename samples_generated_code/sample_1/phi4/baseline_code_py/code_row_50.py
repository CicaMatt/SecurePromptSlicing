import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
        buffer = bytearray(buffer_size)
        
        print(f"Buffer of size {buffer_size} allocated:")
        for i in range(buffer_size):
            print(buffer[i], end=' ')
        print()
    
    except ValueError:
        print("Please provide a valid integer for the buffer size.")

if __name__ == "__main__":
    main()