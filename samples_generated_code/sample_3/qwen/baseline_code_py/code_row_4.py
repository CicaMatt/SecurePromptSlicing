def get_value_at_index():
    try:
        numbers = [10, 20, 30, 40, 50]
        index = int(input("Enter the index: "))
        return numbers[index]
    except IndexError:
        return "Index is out of range."
    except ValueError:
        return "Please enter a valid integer."

print(get_value_at_index())