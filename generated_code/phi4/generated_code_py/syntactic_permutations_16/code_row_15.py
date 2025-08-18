def get_value_at_index(n):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    if 0 <= n < len(array):
        return array[n]
    else:
        raise IndexError("Index out of range")

input_number = int(input("Enter an integer: "))
try:
    result = get_value_at_index(input_number)
    print(f"The value at index {input_number} is: {result}")
except IndexError as e:
    print(e)