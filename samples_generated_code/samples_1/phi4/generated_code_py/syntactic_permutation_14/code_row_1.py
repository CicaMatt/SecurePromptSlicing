def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50]  # Example sequence
    try:
        index = int(input("Enter an index: "))
        return id_sequence[index]
    except (ValueError, IndexError):
        print("Invalid input or out of range.")
        return None

# Uncomment the line below to run the function and see its output.
# print(get_value_from_index())