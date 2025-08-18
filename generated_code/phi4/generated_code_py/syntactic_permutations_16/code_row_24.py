def get_value_at_index(input_array, index):
    try:
        return input_array[index]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    # Example array
    arr = [10, 20, 30, 40, 50, 60]

    # Input from user
    index = int(input("Enter the index: "))
    
    # Get value at the given index
    result = get_value_at_index(arr, index)
    
    print(f"Value at index {index}: {result}")