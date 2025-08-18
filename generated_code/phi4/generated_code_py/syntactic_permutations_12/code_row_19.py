import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: script.py array_size index")
        sys.exit(1)

    try:
        size = int(sys.argv[1])
        index = int(sys.argv[2])
        array_elements = [int(x) for x in input(f"Enter {size} integers separated by spaces: ").split()]
        
        if len(array_elements) != size:
            print("Error: The number of elements does not match the specified size.")
            sys.exit(1)

    except ValueError as e:
        print("Error:", e)
        sys.exit(1)

    value = getValueFromArray(array_elements, size, index)
    
    if value is None:
        print(f"Index {index} out of bounds for array of size {size}.")
        sys.exit(2)

    sys.exit(value)