import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return

    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer for the index.")
        return

    array = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    if 0 <= index < len(array):
        print(array[index])
    else:
        print("Index out of range.")

if __name__ == "__main__":
    main()