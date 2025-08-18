def get_value_from_array(index, arr):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        raise IndexError("Index out of range")

arr = [10, 20, 30, 40, 50, 60, 70]

index = int(input())
value = get_value_from_array(index, arr)
print(value)