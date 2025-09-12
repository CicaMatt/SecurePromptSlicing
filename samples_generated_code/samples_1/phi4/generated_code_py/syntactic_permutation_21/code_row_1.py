import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return 1
    
    try:
        number = int(sys.argv[1])
        result = number + 1000
        print(result)
    except ValueError:
        print("Please provide a valid integer.")
        return 1

    return 0

if __name__ == "__main__":
    sys.exit(main())