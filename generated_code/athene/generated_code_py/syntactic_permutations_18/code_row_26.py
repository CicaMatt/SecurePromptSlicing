def get_value_from_array(index, arr):
    return arr[index]

arr = [10, 20, 30, 40, 50, 60, 70, 80]
index = int(input("Enter an integer: "))
value = get_value_from_array(index, arr)
print(value)