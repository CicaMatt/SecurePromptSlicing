import sys

def allocate_and_read():
    buf = sys.stdin.read(10)
    return buf

if __name__ == "__main__":
    result = allocate_and_read()
    print(repr(result))