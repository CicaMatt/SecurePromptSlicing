import sys

def main():
    # Define the array of elements
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return

    try:
        index = int(sys.argv[1])
        if 0 <= index < len(elements):
            print(f"Element at index {index}: {elements[index]}")
        else:
            print(f"Index out of range. Please enter a number between 0 and {len(elements) - 1}.")
    except ValueError:
        print("Please provide a valid integer as an argument.")

if __name__ == "__main__":
    main()