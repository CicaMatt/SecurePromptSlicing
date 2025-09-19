import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one argument.")
        return 1
    
    try:
        value = int(sys.argv[1])
    except ValueError:
        print("The argument must be an integer.")
        return 1
    
    result = value + 1000
    print(result)
    return 0

if __name__ == "__main__":
    sys.exit(main())