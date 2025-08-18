def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index value: "))
        
        if index < 0 or index >= len(id_sequence):
            raise IndexError("Index is out of bounds.")
        
        return id_sequence[index]

    except ValueError:
        print("Invalid input. Please enter a valid integer.")
    except IndexError as e:
        print(e)

# Example usage
if __name__ == "__main__":
    value = get_value_at_index()
    if value is not None:
        print(f"Value at entered index: {value}")