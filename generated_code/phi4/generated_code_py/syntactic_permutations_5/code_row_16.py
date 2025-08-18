import sys

def main():
    # Array of elements
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    # Check if the correct number of arguments are provided
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        sys.exit(1)

    try:
        # Convert command line argument to an integer index
        index = int(sys.argv[1])
        
        # Print element at the given index
        print(elements[index])
    
    except ValueError:
        print("Please provide a valid integer as an index.")
        sys.exit(1)
    except IndexError:
        print(f"Index {index} is out of range for the list.")
        sys.exit(1)

if __name__ == "__main__":
    main()