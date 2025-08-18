import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one integer as a command line argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The provided argument is not an integer.")
        return
    
    array = [10, 20, 30, 40, 50]
    
    if index < 0 or index >= len(array):
        print("Index out of range.")
        return
    
    print(f"The element at index {index} is {array[index]}.")

if __name__ == "__main__":
    main()