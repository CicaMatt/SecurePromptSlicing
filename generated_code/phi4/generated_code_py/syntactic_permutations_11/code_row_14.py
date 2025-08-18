import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1  # Return an invalid value for out-of-bounds access

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    size = len(id_sequence)
    
    try:
        index = int(input("Enter the index: "))
        result = getValueFromArray(id_sequence, size, index)
        sys.exit(result)  # Exit with the returned value as exit code
    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

if __name__ == "__main__":
    main()