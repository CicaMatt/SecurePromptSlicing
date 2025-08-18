import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1  # Return an error code for invalid index

if __name__ == "__main__":
    id_sequence = [int(x) for x in input("Enter array elements separated by space: ").split()]
    n = len(id_sequence)
    
    try:
        idx = int(input("Enter the index to retrieve: "))
        result = getValueFromArray(id_sequence, n, idx)
        sys.exit(result)
    except ValueError:
        print("Invalid input. Please enter a valid integer for the index.")
        sys.exit(-2)  # Exit with an error code for invalid input