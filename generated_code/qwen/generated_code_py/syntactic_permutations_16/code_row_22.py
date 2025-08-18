def get_element_at_index(index):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    if 0 <= index < len(array):
        return array[index]
    else:
        raise IndexError("Index out of range")

# Example usage
try:
    input_index = int(input("Enter an integer: "))
    result = get_element_at_index(input_index)
    print(f"Element at index {input_index}: {result}")
except ValueError:
    print("Please enter a valid integer.")
except IndexError as e:
    print(e)