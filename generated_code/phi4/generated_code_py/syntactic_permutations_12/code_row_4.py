import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    input_value = int(input().strip())
    array = [int(x) for x in input("Enter the array elements separated by space: ").split()]
    
    value_at_index = getValueFromArray(array, len(array), input_value)
    sys.exit(value_at_index)