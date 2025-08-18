import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return None

if __name__ == "__main__":
    try:
        input_number = int(input().strip())
        array = [i for i in range(1, input_number + 1)]
        size = len(array)
        
        # Example: getting value at index 2
        index_to_fetch = 2
        result = getValueFromArray(array, size, index_to_fetch)

        if result is not None:
            sys.exit(result)
        else:
            sys.exit(0)  # or any appropriate error code
    except Exception as e:
        sys.exit(1)