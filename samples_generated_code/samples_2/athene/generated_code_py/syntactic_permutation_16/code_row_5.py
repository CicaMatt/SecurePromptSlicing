def get_value_from_array(index, arr):
    if index < 0 or index >= len(arr):
        return None
    return arr[index]

arr = [10, 20, 30, 40, 50, 60, 70]
index = int(input())
print(get_value_from_array(index, arr))