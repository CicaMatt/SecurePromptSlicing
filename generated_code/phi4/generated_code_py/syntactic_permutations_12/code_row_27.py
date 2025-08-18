import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        array_input = input().strip()
        n = int(input().strip())
        
        # Convert the string to a list of integers
        array = [int(x) for x in array_input.split()]
        
        index = int(input().strip())
        
        result = getValueFromArray(array, len(array), index)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()