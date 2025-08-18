def get_value_at_index(arr, idx):
    try:
        return arr[idx]
    except IndexError:
        return "Index out of range"

if __name__ == "__main__":
    array = [10, 20, 30, 40, 50, 60, 70]  # Example array
    index = int(input("Enter the index: "))
    result = get_value_at_index(array, index)
    print(result)