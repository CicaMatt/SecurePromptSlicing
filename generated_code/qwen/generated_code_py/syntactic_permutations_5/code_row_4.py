import sys

def main():
    array = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    try:
        index = int(sys.argv[1])
        print(array[index])
    except (IndexError, ValueError):
        print("Please provide a valid integer index as a command line argument.")

if __name__ == "__main__":
    main()