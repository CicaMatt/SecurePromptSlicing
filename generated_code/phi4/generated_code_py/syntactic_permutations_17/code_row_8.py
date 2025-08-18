def get_value_from_index():
    # Input array from user
    array = input("Enter elements of the array separated by space: ").split()
    
    # Convert each element to the appropriate type (assuming integers)
    try:
        array = [int(x) for x in array]
    except ValueError:
        print("Please enter valid integer values.")
        return
    
    # Input index from user
    try:
        index = int(input("Enter the index of the element you want to retrieve: "))
        
        # Check if the index is within range
        if 0 <= index < len(array):
            print(f"The value at index {index} is: {array[index]}")
        else:
            print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Please enter a valid integer for the index.")

get_value_from_index()