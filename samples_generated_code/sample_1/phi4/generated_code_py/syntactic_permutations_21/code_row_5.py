import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return 1
    
    try:
        input_value = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer.")
        return 1

    result = input_value + 10
    print(result)
    
    return 0

if __name__ == "__main__":
    sys.exit(main())