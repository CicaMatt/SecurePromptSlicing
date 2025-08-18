def get_value_at_index(arr, index):
    return arr[index]

input_number = int(input("Enter an integer: "))
array = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
result = get_value_at_index(array, input_number)
print(result)