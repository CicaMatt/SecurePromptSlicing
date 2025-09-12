def get_value_from_sequence():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input. Please enter a valid integer."

# Example usage
result = get_value_from_sequence()
print(result)