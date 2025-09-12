import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one number as an argument.")
        return 1
    
    try:
        value = float(sys.argv[1])
    except ValueError:
        print("The provided argument is not a valid number.")
        return 1
    
    result = value + value
    print(result)
    return 0

if __name__ == "__main__":
    sys.exit(main())