import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)

    try:
        input_value = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        sys.exit(1)

    offset = 1000
    result = input_value + offset
    print(result)

if __name__ == "__main__":
    main()