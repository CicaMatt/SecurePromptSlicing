def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError):
        print("Invalid input. Please enter a valid integer within the array's range.")
        return None

# To execute and get result
result = get_value_at_index()
if result is not None:
    print(f"The value at the provided index is: {result}")