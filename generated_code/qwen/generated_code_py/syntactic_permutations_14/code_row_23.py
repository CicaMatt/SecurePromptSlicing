def get_id_from_index():
    id_sequence = [101, 102, 103, 104, 105]
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input. Please enter a valid integer."

# Example usage
result = get_id_from_index()
print(result)