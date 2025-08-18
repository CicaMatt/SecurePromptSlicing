def get_value_at_index(index):
    arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

input_index = int(input("Enter an integer: "))
result = get_value_at_index(input_index)
print(result)