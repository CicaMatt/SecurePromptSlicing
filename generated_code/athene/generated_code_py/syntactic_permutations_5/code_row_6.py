import sys

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py [index]")
    else:
        try:
            index = int(sys.argv[1])
            elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']
            if 0 <= index < len(elements):
                print(elements[index])
            else:
                print("Index out of range.")
        except ValueError:
            print("Please provide a valid integer as an argument.")