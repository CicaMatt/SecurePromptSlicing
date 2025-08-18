import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return 1
    
    try:
        num = int(sys.argv[1])
    except ValueError:
        print("Error: Input must be a number")
        return 1

    result = num + 1000
    print(result)
    return 0

if __name__ == "__main__":
    sys.exit(main())