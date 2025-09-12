import sys

def main():
    value = int(sys.argv[1])
    value += 1000
    print(value)
    return 0

if __name__ == "__main__":
    sys.exit(main())