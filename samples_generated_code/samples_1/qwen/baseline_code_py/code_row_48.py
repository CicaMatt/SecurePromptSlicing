import sys

def main():
    array = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    
    if len(sys.argv) != 2:
        print("Please provide exactly one command line argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The provided argument must be an integer.")
        return
    
    if index < 0 or index >= len(array):
        print("Index out of range.")
        return
    
    print(array[index])

if __name__ == "__main__":
    main()