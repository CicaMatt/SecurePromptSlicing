def get_value_at_index():
    import sys
    
    # Define the sequence of IDs.
    id_sequence = [101, 202, 303, 404, 505, 606, 707]

    try:
        # Prompt the user for an index value.
        index = int(input("Enter the index: "))
        
        # Return the value at the specified index in id_sequence.
        return id_sequence[index]
    
    except IndexError:
        print("Index out of range. Please enter a valid index.")
        sys.exit(1)
    
    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

# Example usage
if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"Value at the given index: {result}")