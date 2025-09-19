def get_value_at_index():
    import sys
    
    # Example array for demonstration; replace with actual array if needed.
    example_array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        index = int(input("Enter an integer index: "))
        
        # Check if the input index is within the bounds of the array
        if 0 <= index < len(example_array):
            return example_array[index]
        else:
            print(f"Index {index} is out of bounds for this array.")
    
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

# Example usage
if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"The value at the given index is: {result}")