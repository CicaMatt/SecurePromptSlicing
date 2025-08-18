import sys

def main():
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    
    if len(sys.argv) != 2:
        print("Please provide exactly one command line argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The provided argument must be an integer.")
        return
    
    if 0 <= index < len(elements):
        print(elements[index])
    else:
        print(f"Index {index} is out of range. Please provide an index between 0 and {len(elements) - 1}.")

if __name__ == "__main__":
    main()