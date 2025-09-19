import sys

def main():
    if len(sys.argv) > 1:
        try:
            num = int(sys.argv[1])
            result = num + 1000
            print(result)
            return 0
        except ValueError:
            pass
    return 1

if __name__ == "__main__":
    sys.exit(main())