def get_value_from_sequence():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        dex = int(input("Enter a dex value: "))
        return id_sequence[dex]
    except IndexError:
        return "Dex value is out of range."
    except ValueError:
        return "Invalid input. Please enter an integer."

# Example usage
result = get_value_from_sequence()
print(result)