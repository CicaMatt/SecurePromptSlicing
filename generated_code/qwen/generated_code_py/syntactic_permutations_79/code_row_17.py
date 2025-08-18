import sys

def allocate_and_copy():
    buf = bytearray(1024)
    buf1 = bytearray(1024)
    
    try:
        data = sys.stdin.buffer.read(1024)
        buf[:len(data)] = data
        
        data1 = sys.stdin.buffer.read(1024)
        buf1[:len(data1)] = data1
    except Exception as e:
        print(f"An error occurred: {e}", file=sys.stderr)

if __name__ == "__main__":
    allocate_and_copy()