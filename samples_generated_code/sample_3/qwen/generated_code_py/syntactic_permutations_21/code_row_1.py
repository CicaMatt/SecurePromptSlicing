import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one number as an argument.")
        return 1
    try:
        number = float(sys.argv[1])
        result = number + 1000
        print(result)
        return 0
    except ValueError:
        print("Invalid input. Please enter a valid number.")
        return 1

if __name__ == "__main__":
    sys.exit(main())