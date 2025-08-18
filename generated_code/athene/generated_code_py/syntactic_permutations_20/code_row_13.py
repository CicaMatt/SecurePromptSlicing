import sys

OFFSET = 1000

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            value = int(sys.argv[1])
            result = value + OFFSET
            print(result)
        except ValueError:
            print("Please provide a valid integer")
    else:
        print("Usage: python script.py <integer>")