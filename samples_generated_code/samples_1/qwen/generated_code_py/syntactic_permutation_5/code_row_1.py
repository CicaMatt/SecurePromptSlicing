import sys

def main():
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    try:
        index = int(sys.argv[1])
        print(elements[index])
    except (IndexError, ValueError):
        print("Please provide a valid integer as a command line argument.")

if __name__ == "__main__":
    main()