import sys

def allocate_and_copy():
    buf = bytearray(1024)
    buf1 = bytearray(1024)
    
    try:
        data = sys.stdin.buffer.read(1024)
        data_len = len(data)
        
        for i in range(min(data_len, 100)):
            buf[i] = data[i]
            buf1[i] = data[i]
            
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    allocate_and_copy()