def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example array
    try:
        index = int(input("Enter an integer: "))
        if 0 <= index < len(arr):
            return arr[index]
        else:
            return "Index out of range"
    except ValueError:
        return "Invalid input"

print(get_value_at_index())