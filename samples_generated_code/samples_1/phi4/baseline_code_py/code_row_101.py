def get_value_at_index(index):
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return "Index out of range"

input_value = int(input("Enter an integer: "))
result = get_value_at_index(input_value)
print(result)