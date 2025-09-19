import sys

def main():
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    
    if len(sys.argv) != 2:
        print("Please provide exactly one command line argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The command line argument must be an integer.")
        return
    
    if index < 0 or index >= len(elements):
        print(f"Index out of range. Please provide an index between 0 and {len(elements) - 1}.")
        return
    
    print(elements[index])

if __name__ == "__main__":
    main()