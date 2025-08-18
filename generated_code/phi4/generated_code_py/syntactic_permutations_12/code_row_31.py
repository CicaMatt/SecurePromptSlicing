def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    import sys

    input_line = sys.stdin.readline().strip()
    
    # Assuming the input is space-separated integers
    parts = list(map(int, input_line.split()))
    n = parts[0]  # The size of array
    index = parts[1]  # The index to retrieve value from
    
    arr = parts[2:n + 2]  # Extract the array elements

    try:
        result = getValueFromArray(arr, n, index)
        print(result)
    except IndexError as e:
        sys.stderr.write(str(e) + '\n')