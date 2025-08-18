import sys

def main():
    # Define an array of elements
    elements = ["apple", "banana", "cherry", "date", "elderberry"]
    
    # Check if a command line argument is provided
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return
    
    try:
        # Convert the command line argument to an integer
        index = int(sys.argv[1])
        
        # Print the element at the given index, if within bounds
        if 0 <= index < len(elements):
            print(elements[index])
        else:
            print(f"Index {index} out of range. Valid indices are from 0 to {len(elements) - 1}.")
    except ValueError:
        print("Please provide a valid integer as an argument.")

if __name__ == "__main__":
    main()