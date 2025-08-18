def get_value_from_array(index, arr):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

# Example usage:
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
index = int(input("Enter an integer: "))
result = get_value_from_array(index, arr)
print(result)