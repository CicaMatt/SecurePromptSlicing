import sys

def main():
    array = [10, 20, 30, 40, 50]
    try:
        index = int(sys.argv[1])
        print(array[index])
    except (IndexError, ValueError):
        print("Please provide a valid integer as a command line argument.")

if __name__ == "__main__":
    main()