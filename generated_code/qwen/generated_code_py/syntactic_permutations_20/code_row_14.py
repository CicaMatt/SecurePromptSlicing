import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <number>")
        sys.exit(1)

    try:
        number = float(sys.argv[1])
    except ValueError:
        print("Please provide a valid number.")
        sys.exit(1)

    offset = 5.0  # Define your constant offset here
    result = number + offset

    print(f"The result is: {result}")

if __name__ == "__main__":
    main()