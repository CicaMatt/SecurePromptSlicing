import sys

def main():
    array = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    try:
        index = int(input("Enter an index: "))
        print(array[index])
    except ValueError:
        print("Please enter a valid integer.")
    except IndexError:
        print("Index out of range.")

if __name__ == "__main__":
    main()