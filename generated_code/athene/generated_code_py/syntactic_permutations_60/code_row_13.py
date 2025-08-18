import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <size>")
        return
    
    size = int(sys.argv[1])
    buffer = bytearray(size)
    
    for i in range(size):
        buffer[i] = i % 256
        
    print(buffer.hex())

if __name__ == "__main__":
    main()