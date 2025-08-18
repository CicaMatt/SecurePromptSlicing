def get_value_at_index(index):
    sample_list = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    if 0 <= index < len(sample_list):
        return sample_list[index]
    else:
        raise IndexError("Index out of range")

# Example usage
input_index = int(input("Enter an integer: "))
try:
    result = get_value_at_index(input_index)
    print(f"The value at index {input_index} is {result}.")
except IndexError as e:
    print(e)