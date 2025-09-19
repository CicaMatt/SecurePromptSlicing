def get_value_from_index():
    import sys

    id_sequence = [10, 20, 30, 40, 50]  # Example sequence, adjust as needed.

    try:
        index = int(input("Enter an index value: "))
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print(f"Index {index} is out of range.")
            sys.exit(1)
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        sys.exit(1)

# Uncomment the line below to test the function
# print(get_value_from_index())