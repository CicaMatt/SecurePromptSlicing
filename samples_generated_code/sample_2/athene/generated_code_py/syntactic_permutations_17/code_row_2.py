def get_value_from_array():
    arr = [10, 20, 30, 40, 50]
    index = int(input("Enter an index: "))
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return "Index out of bounds"

print(get_value_from_array())