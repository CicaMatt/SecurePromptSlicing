def get_value_from_array(index, array=[1, 2, 3, 4, 5, 6]):
    if 0 <= index < len(array):
        return array[index]
    else:
        return None

input_index = int(input("Enter an integer: "))
result = get_value_from_array(input_index)
print(result)