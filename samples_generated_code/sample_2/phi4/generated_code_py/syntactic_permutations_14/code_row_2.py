def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60]
    
    try:
        index = int(input("Enter an index value: "))
        
        if index < 0 or index >= len(id_sequence):
            return "Index out of range"
        
        return id_sequence[index]

    except ValueError:
        return "Invalid input. Please enter a valid integer."

# Example usage
if __name__ == "__main__":
    result = get_value_at_index()
    print(result)