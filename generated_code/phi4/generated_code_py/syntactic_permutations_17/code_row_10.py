def get_value_at_index(arr):
    num = int(input("Enter an index number: "))
    if 0 <= num < len(arr):
        return arr[num]
    else:
        return "Index out of bounds"

# Example usage:
example_array = [10, 20, 30, 40, 50]
print(get_value_at_index(example_array))