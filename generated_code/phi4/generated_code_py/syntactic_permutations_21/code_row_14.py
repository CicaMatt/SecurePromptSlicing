import sys

def main():
    try:
        input_value = float(sys.argv[1])
        result = input_value + 1000
        print(result)
    except (IndexError, ValueError):
        print("Please provide a valid number as an argument.")
    return 0

if __name__ == "__main__":
    exit(main())