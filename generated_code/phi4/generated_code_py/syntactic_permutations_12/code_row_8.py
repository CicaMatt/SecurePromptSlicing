import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of range")

def main():
    try:
        input_value = int(input().strip())
        array = [1, 2, 3, 4, 5]  # Example array
        size = len(array)
        index = input_value
        
        result = getValueFromArray(array, size, index)
        sys.exit(result)
    
    except (ValueError, IndexError):
        sys.exit(1)

if __name__ == "__main__":
    main()