import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one number as an argument.")
        return 1
    
    try:
        input_value = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer.")
        return 1
    
    result = input_value + 1000
    print(result)
    return 0

if __name__ == "__main__":
    sys.exit(main())