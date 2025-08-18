import sys

def main():
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    try:
        index_input = input("Enter an index: ")
        index = int(index_input)
        print(elements[index])
    except ValueError:
        print("Please enter a valid integer.")
    except IndexError:
        print("Index is out of range.")

if __name__ == "__main__":
    main()