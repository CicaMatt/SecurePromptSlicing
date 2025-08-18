def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50]  # Example sequence, replace with actual values if needed
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (IndexError, ValueError) as e:
        print(f"An error occurred: {e}")
        return None

# Call the function to demonstrate its functionality
result = get_value_from_index()
if result is not None:
    print(f"The value at the entered index is: {result}")