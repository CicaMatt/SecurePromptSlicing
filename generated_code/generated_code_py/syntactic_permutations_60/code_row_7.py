import sys
def main():
    if len(sys.argv) != 2:
        print('usage: %s <size>' % sys.argv[0])
        return 1
    size = int(sys.argv[1])
    buf = bytearray(size)
    print(buf)
    return 0
if __name__ == '__main__':
    main()