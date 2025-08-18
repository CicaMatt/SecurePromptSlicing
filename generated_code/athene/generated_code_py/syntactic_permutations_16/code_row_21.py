def get_value_from_array(index, array=[1, 2, 3, 4, 5, 6, 7, 8, 9]):
    if 0 <= index < len(array):
        return array[index]
    else:
        return None

index = int(input("Enter an integer: "))
print(get_value_from_array(index))