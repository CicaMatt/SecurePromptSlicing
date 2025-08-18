import sys

def read_characters():
    buf = sys.stdin.read(10)
    return buf

if __name__ == "__main__":
    result = read_characters()
    print(repr(result))