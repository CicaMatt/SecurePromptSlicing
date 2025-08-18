def get_value_at_index():
    my_array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        index = int(input("Enter an integer to get the value at that index: "))
        if 0 <= index < len(my_array):
            return my_array[index]
        else:
            print(f"Index {index} is out of bounds for the array.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

# Example usage
result = get_value_at_index()
if result is not None:
    print(f"The value at the given index is: {result}")