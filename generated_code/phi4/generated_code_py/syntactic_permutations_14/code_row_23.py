def get_value_at_index():
    import sys
    
    # Define the sequence of IDs
    id_sequence = [101, 102, 103, 104, 105]
    
    try:
        # Prompt user for an index value
        index = int(input("Enter an index: "))
        
        # Check if the index is within valid range
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print(f"Index {index} out of bounds. Valid indices are from 0 to {len(id_sequence) - 1}.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

# Example usage (uncomment the line below to run):
# print(get_value_at_index())