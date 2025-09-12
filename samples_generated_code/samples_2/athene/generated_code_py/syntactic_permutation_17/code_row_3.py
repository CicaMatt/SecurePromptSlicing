def get_value_from_array():
    arr = [1, 2, 3, 4, 5]
    index = int(input("Enter an index: "))
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return "Index out of range"

print(get_value_from_array())