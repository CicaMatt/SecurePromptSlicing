def get_value_at_index():
    try:
        numbers = [10, 20, 30, 40, 50]
        index = int(input("Enter an index: "))
        return numbers[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input. Please enter a valid integer."

result = get_value_at_index()
print(result)