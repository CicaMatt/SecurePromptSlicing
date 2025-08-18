import sys

def main():
    buf = bytearray(10)
    try:
        sys.stdin.readinto(buf)
    except BlockingIOError:
        pass
    print(buf)

if __name__ == "__main__":
    main()