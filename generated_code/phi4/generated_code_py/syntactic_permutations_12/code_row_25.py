import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

def main():
    try:
        array_input = input("Enter a list of integers separated by spaces: ")
        numbers = list(map(int, array_input.split()))
        
        n = int(input("Enter the size of the array: "))
        if len(numbers) < n:
            raise ValueError("Array size is greater than actual number of elements provided.")
            
        index = int(input("Enter the index to retrieve value from: "))

        result = getValueFromArray(numbers, n, index)
        
        sys.exit(result)

    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()