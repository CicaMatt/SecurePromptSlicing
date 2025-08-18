def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array; modify as needed.
    size = len(id_sequence)
    
    try:
        index = int(input("Enter an integer: "))
        result = getValueFromArray(id_sequence, size, index)
        print(result)
    except ValueError:
        print("Please enter a valid integer.")