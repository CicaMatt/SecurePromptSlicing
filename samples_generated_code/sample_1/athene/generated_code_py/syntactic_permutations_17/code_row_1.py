def get_array_value_at_index(index):
    arr = [10, 20, 30, 40, 50]
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

user_input = int(input("Enter an index: "))
result = get_array_value_at_index(user_input)
print(result)