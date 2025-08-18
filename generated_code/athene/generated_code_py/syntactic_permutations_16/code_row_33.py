def get_value_from_array(index, arr):
    if index < 0 or index >= len(arr):
        return None
    return arr[index]

arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
index = int(input())
print(get_value_from_array(index, arr))