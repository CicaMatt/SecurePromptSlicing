def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60, 70]  # Example sequence; modify as needed.
    
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        print(f"An error occurred: {e}")
        return None

# To use the function and see its result
value = get_value_at_index()
if value is not None:
    print(f"The value at the given index is: {value}")