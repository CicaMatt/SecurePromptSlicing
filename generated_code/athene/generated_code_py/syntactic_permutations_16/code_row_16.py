def get_value_from_array(index):
    arr = [1, 2, 3, 4, 5, 6]
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

input_index = int(input())
result = get_value_from_array(input_index)
print(result)