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
        
        print(f"Buffer contents (size {buffer_size}):")
        for i, byte in enumerate(buffer):
            print(f"Index {i}: {byte}")
    
    except ValueError as e:
        print(e)

if __name__ == "__main__":
    main()