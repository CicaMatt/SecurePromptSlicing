import sys

if __name__ == '__main__':
    if len(sys.argv) > 1:
        n = int(sys.argv[1]) + 1000
        print("n=", n)
        sys.exit(0)