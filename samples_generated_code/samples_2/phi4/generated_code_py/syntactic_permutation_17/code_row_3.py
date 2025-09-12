def get_value_from_array():
    try:
        # Input the size of the array
        n = int(input("Enter the size of the array: "))
        
        # Initialize the array with input values
        arr = []
        for i in range(n):
            value = float(input(f"Enter element {i+1} of the array: "))
            arr.append(value)
        
        # Input the position to access in the array
        index = int(input("Enter the index of the element you want to retrieve (0-based): "))
        
        # Check if the index is within bounds
        if 0 <= index < n:
            print(f"The value at index {index} is: {arr[index]}")
        else:
            print("Index out of range. Please enter a valid index.")
    
    except ValueError as e:
        print("Invalid input. Please ensure you are entering numeric values.")

get_value_from_array()