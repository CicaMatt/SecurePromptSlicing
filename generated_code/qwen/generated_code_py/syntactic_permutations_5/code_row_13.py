import sys

def main():
    array = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    if len(sys.argv) > 1:
        try:
            index = int(sys.argv[1])
            print(array[index])
        except (ValueError, IndexError):
            print("Invalid index provided.")
    else:
        print("No index provided.")

if __name__ == "__main__":
    main()