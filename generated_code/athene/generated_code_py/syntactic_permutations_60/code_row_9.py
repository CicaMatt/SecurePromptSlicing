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

    buffer = bytearray(buffer_size)
    
    for i in range(buffer_size):
        byte_value = (i % 256)  # Cycle through 0 to 255
        buffer[i] = byte_value
    
    print(buffer)

if __name__ == "__main__":
    main()