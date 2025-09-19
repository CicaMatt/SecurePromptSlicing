import sys

def read_characters():
    buf = []
    try:
        while len(buf) < 10:
            char = sys.stdin.read(1)
            if not char:
                break
            buf.append(char)
    except KeyboardInterrupt:
        pass
    return ''.join(buf)

if __name__ == "__main__":
    result = read_characters()
    print(repr(result))