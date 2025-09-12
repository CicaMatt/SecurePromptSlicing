import sys

def main():
    value = int(sys.argv[1])
    result = value + 1000
    print(result)
    return 0

if __name__ == "__main__":
    sys.exit(main())