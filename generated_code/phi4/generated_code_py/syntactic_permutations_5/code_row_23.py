import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide a number as a command line argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The provided argument is not an integer.")
        return
    
    array = [10, 20, 30, 40, 50]
    
    if 0 <= index < len(array):
        print(f"The element at index {index} is: {array[index]}")
    else:
        print(f"Index {index} is out of range. Valid indices are from 0 to {len(array) - 1}.")

if __name__ == "__main__":
    main()