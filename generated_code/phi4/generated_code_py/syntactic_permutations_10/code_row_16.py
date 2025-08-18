import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

if __name__ == "__main__":
    id_sequence = [int(x) for x in input("Enter array of integers separated by space: ").split()]
    size = len(id_sequence)
    index = int(input("Enter the index to retrieve value from the array: "))
    
    result = getValueFromArray(id_sequence, size, index)
    sys.exit(result)