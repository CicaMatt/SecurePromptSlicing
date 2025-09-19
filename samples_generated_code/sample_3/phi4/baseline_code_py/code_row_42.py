def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        index = int(input("Enter an integer: "))
        return arr[index]
    except IndexError:
        return "Index out of range."
    except ValueError:
        return "Invalid input. Please enter an integer."

print(get_value_at_index())