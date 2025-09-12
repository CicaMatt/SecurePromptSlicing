def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60]  # Example array; replace with your actual data
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (IndexError, ValueError):
        print("Invalid index. Please enter a valid integer within the range of the array.")
        return None

result = get_value_at_index()
if result is not None:
    print(f"Value at the given index: {result}")