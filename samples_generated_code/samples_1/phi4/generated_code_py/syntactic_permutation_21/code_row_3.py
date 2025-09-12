import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        return 1
    
    try:
        input_value = float(sys.argv[1])
        result = input_value + 1000
        print(result)
    except ValueError:
        print("Please enter a valid number.")
        return 1

    return 0

if __name__ == "__main__":
    sys.exit(main())