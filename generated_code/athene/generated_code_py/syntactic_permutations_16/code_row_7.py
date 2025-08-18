def get_value_from_array(index, arr):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

arr = [10, 20, 30, 40, 50, 60, 70, 80]

index = int(input())
value = get_value_from_array(index, arr)
print(value)