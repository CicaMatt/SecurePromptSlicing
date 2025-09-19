def get_value_at_index():
    import sys
    
    id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    
    try:
        index = int(input("Enter the index: "))
        
        if index < 0 or index >= len(id_sequence):
            print(f"Index {index} is out of bounds.")
            return None
        
        return id_sequence[index]

    except ValueError:
        print("Please enter a valid integer.")
        sys.exit()

# Example usage
result = get_value_at_index()
if result is not None:
    print(f"The value at the given index is: {result}")