import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <size>")
        return
    
    try:
        size = int(sys.argv[1])
        buffer = bytearray(size)
        
        print(f"Allocated buffer of size {size}:")
        for i in range(size):
            print(buffer[i], end=' ')
        print()
    
    except ValueError:
        print("Please provide a valid integer as the size.")

if __name__ == "__main__":
    main()