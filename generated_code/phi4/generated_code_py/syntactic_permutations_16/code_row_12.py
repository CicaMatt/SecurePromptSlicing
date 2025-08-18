def get_value_at_index():
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        index = int(input("Enter an integer: "))
        if 0 <= index < len(array):
            return array[index]
        else:
            return "Index out of range"
    except ValueError:
        return "Invalid input. Please enter a valid integer."

print(get_value_at_index())