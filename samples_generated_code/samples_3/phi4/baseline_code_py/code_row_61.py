import sys

def main():
    # Check if there are enough arguments provided
    if len(sys.argv) < 2:
        print("Usage: python script.py <index>")
        sys.exit(1)

    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer as the command line argument.")
        sys.exit(1)
    
    # Define an array of elements
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    try:
        element_at_index = elements[index]
        print(f"Element at index {index}: {element_at_index}")
    except IndexError:
        print(f"No element found at index {index}. Please provide an index between 0 and {len(elements) - 1}.")

if __name__ == "__main__":
    main()