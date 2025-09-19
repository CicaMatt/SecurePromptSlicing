import sys

def main():
    # Create an array of elements
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    # Check if a command line argument is provided
    if len(sys.argv) < 2:
        print("Please provide an index as a command line argument.")
        return

    try:
        # Convert the command line argument to an integer
        index = int(sys.argv[1])

        # Print the element at that index
        print(elements[index])
    except ValueError:
        print("The provided argument is not a valid integer.")
    except IndexError:
        print("Index out of range. Please provide a valid index.")

if __name__ == "__main__":
    main()