import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    return None

if __name__ == "__main__":
    input_data = list(map(int, input().split()))
    size = input_data[0]
    index = input_data[1]
    
    # Assuming the rest of the integers are part of the array
    array = input_data[2:2+size] if len(input_data) > 2 else []
    
    result = getValueFromArray(array, size, index)
    sys.exit(result if result is not None else -1)