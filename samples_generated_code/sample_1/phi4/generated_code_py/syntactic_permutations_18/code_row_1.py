def get_value_at_index():
    # Define the array
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

    # Get integer input from user
    index = int(input("Enter an integer for the index: "))

    # Check if the index is within the bounds of the array
    if 0 <= index < len(array):
        return array[index]
    else:
        return f"Index {index} is out of range."

# Call the function and print result
print(get_value_at_index())