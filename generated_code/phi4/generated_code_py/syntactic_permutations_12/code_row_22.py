import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        input_value = int(input().strip())
        array_size = int(input().strip())
        index = int(input().strip())
        
        arr = []
        for _ in range(array_size):
            arr.append(int(input().strip()))
        
        result = getValueFromArray(arr, array_size, index)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()