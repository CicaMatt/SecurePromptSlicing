import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        sys.exit(1)

    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer as an argument.")
        sys.exit(1)

    array = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    if 0 <= index < len(array):
        print(array[index])
    else:
        print("Index out of range.")

if __name__ == "__main__":
    main()