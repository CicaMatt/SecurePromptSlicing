def get_value_at_index():
    import ast
    
    # Input array as a string
    array_input = input("Enter an array (e.g., [1, 2, 3, 4]): ")
    array = ast.literal_eval(array_input)
    
    # Input index
    index_input = int(input(f"Enter the index to retrieve from {array} (0-based): "))
    
    # Return value at specified index
    try:
        return array[index_input]
    except IndexError:
        print("Index out of range.")
        return None

# Example usage
if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"Value at the given index: {result}")