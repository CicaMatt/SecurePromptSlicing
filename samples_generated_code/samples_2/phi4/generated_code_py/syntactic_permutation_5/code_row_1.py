import sys

def main():
    # Create an array of elements
    elements = ['apple', 'banana', 'cherry', 'date', 'fig']

    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return

    try:
        index = int(sys.argv[1])
        # Print the element at the given index
        print(elements[index])
    except (ValueError, IndexError):
        print(f"Invalid input or index out of range. Available indices are 0 to {len(elements) - 1}.")

if __name__ == "__main__":
    main()