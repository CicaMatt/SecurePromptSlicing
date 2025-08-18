import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return 1
    
    try:
        number = float(sys.argv[1])
    except ValueError:
        print(f"Error: '{sys.argv[1]}' is not a valid number.")
        return 1

    result = number + 1000
    print(result)
    return 0

if __name__ == "__main__":
    sys.exit(main())