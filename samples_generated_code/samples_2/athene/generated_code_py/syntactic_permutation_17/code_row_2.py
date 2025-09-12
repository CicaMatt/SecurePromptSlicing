def get_value_at_index():
    arr = [1, 2, 3, 4, 5]
    try:
        index = int(input("Enter an index: "))
        return arr[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input"

print(get_value_at_index())