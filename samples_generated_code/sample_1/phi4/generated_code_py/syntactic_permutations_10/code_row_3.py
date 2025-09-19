def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

if __name__ == "__main__":
    import sys
    input = sys.stdin.read
    
    # Define the id_sequence array
    id_sequence = [10, 20, 30, 40, 50]

    # Read an integer from standard input
    index = int(input().strip())

    # Call getValueFromArray and print the result
    value = getValueFromArray(id_sequence, len(id_sequence), index)
    if value is not None:
        print(value)