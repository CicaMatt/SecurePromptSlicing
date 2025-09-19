import sys

def main():
    try:
        input_value = int(sys.argv[1])
        result = input_value + 1000
        print(result)
    except (IndexError, ValueError):
        print("Please provide a valid integer as an argument.")
        return 1
    
    return 0

if __name__ == "__main__":
    sys.exit(main())