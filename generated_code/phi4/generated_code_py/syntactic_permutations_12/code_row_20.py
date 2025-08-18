import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

if __name__ == "__main__":
    input_data = sys.stdin.read().strip()
    parts = list(map(int, input_data.split()))
    
    size = parts[0]
    index = parts[1]
    array = parts[2:size+2]
    
    result = getValueFromArray(array, size, index)
    sys.exit(result)