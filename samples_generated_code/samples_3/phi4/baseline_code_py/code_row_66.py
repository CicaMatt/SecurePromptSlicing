import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    try:
        n = int(input().strip())
        array_str = input().strip()
        arr = list(map(int, array_str.split()))
        
        if len(arr) != n:
            print("Array size does not match the provided integer.")
            sys.exit(1)
        
        index_to_access = 0  # Example: Accessing first element. Adjust as needed.
        value = getValueFromArray(arr, n, index_to_access)
        sys.exit(value)
    except Exception as e:
        print(e)
        sys.exit(1)