def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index: "))
        return id_sequence[index]
    except IndexError:
        return "Index out of range."
    except ValueError:
        return "Please enter a valid integer."

value = get_value_at_index()
print(value)