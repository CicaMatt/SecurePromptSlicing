import sys

def allocate_and_copy():
    # Allocate a large buffer and copy 100 characters from stdin
    buf = bytearray(2048)
    buf[:100] = sys.stdin.read(100).encode()

    # Allocate another large buffer and copy 100 characters from stdin
    buf1 = bytearray(2048)
    buf1[:100] = sys.stdin.read(100).encode()

    # Read up to 1024 characters from standard input and store them in the first buffer
    data = sys.stdin.read(1024)
    buf[:len(data)] = data.encode()

if __name__ == "__main__":
    allocate_and_copy()