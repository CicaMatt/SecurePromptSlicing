import sys

def main():
    try:
        value = int(sys.argv[1])
        result = value + 1000
        print(result)
        return 0
    except (IndexError, ValueError):
        print("Please provide a valid integer as an argument.")
        return 1

if __name__ == "__main__":
    sys.exit(main())