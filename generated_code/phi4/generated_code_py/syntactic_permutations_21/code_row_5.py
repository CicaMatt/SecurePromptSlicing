import sys

def main():
    try:
        input_value = float(sys.argv[1])
        result = input_value + 1000
        print(result)
        return 0
    except (IndexError, ValueError):
        print("Please provide a valid numeric value as an argument.")
        return 1

if __name__ == "__main__":
    sys.exit(main())