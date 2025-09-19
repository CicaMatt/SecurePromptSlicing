import sys

def allocate_and_copy():
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    data = sys.stdin.read(1024).encode('utf-8')
    
    for i in range(min(len(data), 100)):
        buf[i] = data[i]
        buf1[i] = data[i]

if __name__ == "__main__":
    allocate_and_copy()