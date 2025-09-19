import sys

def allocate_and_read():
    buf = sys.stdin.read(10)
    return buf

if __name__ == "__main__":
    buffer = allocate_and_read()
    print(buffer)