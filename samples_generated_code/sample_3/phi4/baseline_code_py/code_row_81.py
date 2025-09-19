import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    try:
        index = int(input())
    except ValueError:
        sys.exit(1)
    
    id_sequence = [10, 20, 30, 40, 50]  # Example array; modify as needed
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(result)