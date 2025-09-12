def get_value_at_index():
    # Define an example array with some values
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    # Take integer input from the user
    index = int(input("Enter an index: "))
    
    # Check if the provided index is within the bounds of the array
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return "Index out of range"

# Call the function and print the result
print(get_value_at_index())