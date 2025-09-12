def get_value_at_index():
    import sys
    
    # Sample array, replace or modify as needed.
    id_sequence = [10, 20, 30, 40, 50]
    
    # Prompt the user for an index
    try:
        index = int(input("Enter the index: "))
        
        # Return the value at that index in id_sequence
        return id_sequence[index]
    
    except (ValueError, IndexError):
        print("Invalid input or index out of range.")
        sys.exit(1)

# Example usage: Uncomment to test
# if __name__ == "__main__":
#     result = get_value_at_index()
#     if result is not None:
#         print(f"Value at the given index: {result}")