def get_value_at_index():
    import sys

    id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # Example sequence; modify as needed.
    
    try:
        index = int(input("Enter the index: "))
        
        if index < 0 or index >= len(id_sequence):
            print(f"Index out of range. Valid indices are 0 to {len(id_sequence) - 1}.")
            sys.exit(1)
            
        return id_sequence[index]
    
    except ValueError:
        print("Please enter a valid integer.")
        sys.exit(1)

# Example usage
value = get_value_at_index()
print(f"The value at the given index is: {value}")