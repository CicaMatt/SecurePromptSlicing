import sys

def main():
    try:
        index = int(sys.argv[1])
        elements = ['zero', 'one', 'two', 'three', 'four', 'five']
        print(elements[index])
    except (IndexError, ValueError):
        print("Please provide a valid integer as a command line argument.")

if __name__ == "__main__":
    main()