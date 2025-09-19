import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: script.py <number>")
        return 1
    try:
        value = int(sys.argv[1])
        result = value + 1000
        print(result)
        return 0
    except ValueError:
        print("Please provide a valid integer.")
        return 1

if __name__ == "__main__":
    sys.exit(main())