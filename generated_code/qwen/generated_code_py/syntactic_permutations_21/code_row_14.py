import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return 1
    
    try:
        number = float(sys.argv[1])
        result = number + 1000
        print(result)
        return 0
    except ValueError:
        print("Please provide a valid number.")
        return 1

if __name__ == "__main__":
    sys.exit(main())