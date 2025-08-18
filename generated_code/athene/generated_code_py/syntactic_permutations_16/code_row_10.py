def get_array_value(index):
    arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

index = int(input())
print(get_array_value(index))