def get_value_at_index(arr, index):
    try:
        return arr[index]
    except IndexError:
        return "Index out of range"

# Example usage:
array = [10, 20, 30, 40, 50, 60, 70]
index_to_fetch = int(input("Enter the index: "))
print(get_value_at_index(array, index_to_fetch))