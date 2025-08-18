def find_index_in_array(arr, target):
    try:
        return arr.index(target)
    except ValueError:
        return -1

# Example usage:
array = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
input_number = int(input("Enter an integer: "))
index = find_index_in_array(array, input_number)
print(index)