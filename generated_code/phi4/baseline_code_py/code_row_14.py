def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60]
    
    try:
        index = int(input("Enter an index value: "))
        
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print("Index out of range.")
            return None
    except ValueError:
        print("Invalid input. Please enter an integer.")
        return None

# Example usage (uncomment the line below to test)
# print(get_value_at_index())