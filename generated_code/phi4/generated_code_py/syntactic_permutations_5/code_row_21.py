import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <integer>")
        sys.exit(1)

    try:
        number = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer.")
        sys.exit(1)

    array = [i for i in range(number)]
    print(array)

if __name__ == "__main__":
    main()