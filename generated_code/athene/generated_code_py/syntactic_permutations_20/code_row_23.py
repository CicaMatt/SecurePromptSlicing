import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)
    
    try:
        value = int(sys.argv[1])
        OFFSET = 1000
        result = value + OFFSET
        print(result)
    except ValueError:
        print("Please provide a valid integer.")