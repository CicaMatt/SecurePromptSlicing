def get_value_at_index():
    array = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index value: "))
        return array[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input. Please enter a valid integer."

# Example usage
result = get_value_at_index()
print(result)