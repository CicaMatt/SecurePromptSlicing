def get_value_at_index():
    try:
        array = [10, 20, 30, 40, 50]
        index = int(input("Enter the index: "))
        return array[index]
    except IndexError:
        return "Index out of range."
    except ValueError:
        return "Invalid input. Please enter a valid integer."

result = get_value_at_index()
print(result)