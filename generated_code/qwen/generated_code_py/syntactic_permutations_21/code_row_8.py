import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one number as an argument.")
        return 1
    
    try:
        number = int(sys.argv[1])
    except ValueError:
        print("The provided argument is not a valid integer.")
        return 1
    
    result = number + 1000
    print(result)
    return 0

if __name__ == "__main__":
    sys.exit(main())