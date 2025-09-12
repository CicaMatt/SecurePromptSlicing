import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)

    try:
        value = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        sys.exit(1)

    OFFSET = 1000
    result = value + OFFSET
    print(result)

if __name__ == "__main__":
    main()