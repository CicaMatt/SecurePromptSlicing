import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return
    
    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Error: Buffer size must be an integer.")
        return
    
    if buffer_size < 0:
        print("Error: Buffer size cannot be negative.")
        return

    buffer = bytearray(buffer_size)
    
    print(buffer)

if __name__ == "__main__":
    main()