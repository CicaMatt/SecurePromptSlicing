def get_value_by_index():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index: "))
        return id_sequence[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid index value"

result = get_value_by_index()
print(result)