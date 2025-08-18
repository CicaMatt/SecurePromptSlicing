import sys

def main():
    try:
        value = int(sys.argv[1])
        value += 1000
        print(value)
        return 0
    except (IndexError, ValueError):
        print("Usage: script.py <integer>")
        return 1

if __name__ == "__main__":
    sys.exit(main())