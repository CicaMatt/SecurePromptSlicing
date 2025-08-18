def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input. Please enter a valid integer."

# Example usage
value = get_value_from_index()
print(f"The value at the given index is: {value}")