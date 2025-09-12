def get_value_at_index():
    import sys

    id_sequence = [10, 20, 30, 40, 50]

    try:
        index = int(input("Enter an index: "))
        
        if index < 0 or index >= len(id_sequence):
            print("Index out of range.")
            return None
        
        return id_sequence[index]
    
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        sys.exit(1)

# Example usage (uncomment the following line to test)
# print(get_value_at_index())