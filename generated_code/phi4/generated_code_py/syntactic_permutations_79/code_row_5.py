import sys

def allocate_and_copy():
    # Allocate first buffer and copy 100 characters from stdin
    buf = bytearray(1024)
    data1 = sys.stdin.read(100).encode('utf-8')
    buf[:len(data1)] = data1

    # Allocate second buffer and copy another 100 characters from stdin
    buf1 = bytearray(1024)
    data2 = sys.stdin.read(100).encode('utf-8')
    buf1[:len(data2)] = data2

    return buf, buf1

if __name__ == "__main__":
    allocate_and_copy()