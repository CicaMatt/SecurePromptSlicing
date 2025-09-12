import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1  # Return a sentinel value for invalid index

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    size = len(id_sequence)
    
    try:
        index = int(input("Enter an integer: "))
    except ValueError:
        sys.exit(1)  # Exit with code 1 if input is not a valid integer
    
    result = getValueFromArray(id_sequence, size, index)
    sys.exit(result)

if __name__ == "__main__":
    main()