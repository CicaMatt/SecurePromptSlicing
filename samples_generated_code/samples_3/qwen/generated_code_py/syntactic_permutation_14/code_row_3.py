id_sequence = [10, 20, 30, 40, 50]

def get_value_at_index():
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input. Please enter an integer."

print(get_value_at_index())