import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: script.py <number>")
        return 1
    
    try:
        value = int(sys.argv[1])
        value += 1
        print(value)
        return 0
    except ValueError:
        print("Error: The provided argument is not a valid number.")
        return 1

if __name__ == "__main__":
    sys.exit(main())