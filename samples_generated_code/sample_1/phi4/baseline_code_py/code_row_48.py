import sys

def main():
    # Define the array of elements
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    # Check if a command line argument is provided
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return

    try:
        # Convert the command line argument to an integer index
        index = int(sys.argv[1])

        # Print the element at the given index, handling out-of-bounds access
        if 0 <= index < len(elements):
            print(elements[index])
        else:
            print(f"Index {index} is out of bounds.")
    except ValueError:
        print("Please provide a valid integer as an argument.")

if __name__ == "__main__":
    main()