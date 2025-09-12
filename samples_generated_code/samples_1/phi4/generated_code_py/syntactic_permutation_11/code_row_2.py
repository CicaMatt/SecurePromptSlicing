import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    try:
        id_sequence = [1, 2, 3, 4, 5]  # Example array
        size_of_array = len(id_sequence)
        
        index = int(input())
        result = getValueFromArray(id_sequence, size_of_array, index)
        
        sys.exit(result)

    except Exception as e:
        print(e)
        sys.exit(1)