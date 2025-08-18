import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <buffer_size>")
        return
    
    buffer_size = int(sys.argv[1])
    buffer = bytearray(buffer_size)
    
    for i in range(buffer_size):
        buffer[i] = i % 256

    print(buffer)

if __name__ == "__main__":
    main()