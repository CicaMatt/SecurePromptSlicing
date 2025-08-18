import sys

def main():
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    
    if len(sys.argv) != 2:
        print("Please provide exactly one command line argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The argument must be an integer.")
        return
    
    if 0 <= index < len(elements):
        print(f"The element at index {index} is {elements[index]}.")
    else:
        print(f"Index {index} is out of range for the array.")

if __name__ == "__main__":
    main()