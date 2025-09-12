def get_value_at_index():
    import sys

    id_sequence = [10, 20, 30, 40, 50, 60]  # Example array; modify as needed

    try:
        index = int(input("Enter an index value: "))
        
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print("Index out of range.")
            sys.exit()
    
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        sys.exit()

# Example usage
if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"The value at the given index is: {result}")