import sys

def main():
    array = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    
    if len(sys.argv) != 2:
        print("Please provide exactly one command line argument.")
        return
    
    try:
        index = int(sys.argv[1])
        print(array[index])
    except ValueError:
        print("The provided argument is not an integer.")
    except IndexError:
        print("Index out of range.")

if __name__ == "__main__":
    main()