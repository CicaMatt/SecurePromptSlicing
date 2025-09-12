import sys

def main():
    # Array of elements
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return

    try:
        index = int(sys.argv[1])
        # Check if the index is within bounds
        if 0 <= index < len(elements):
            print(f"The element at index {index} is '{elements[index]}'")
        else:
            print("Index out of range.")
    except ValueError:
        print("Please provide a valid integer as an argument.")

if __name__ == "__main__":
    main()