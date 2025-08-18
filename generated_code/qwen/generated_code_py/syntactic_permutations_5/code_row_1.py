import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one command line argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The command line argument must be an integer.")
        return

    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    
    if 0 <= index < len(elements):
        print(elements[index])
    else:
        print("Index is out of range.")

if __name__ == "__main__":
    main()