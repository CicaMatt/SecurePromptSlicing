def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        index = int(input("Enter an integer for the index: "))
        if index < len(arr):
            return arr[index]
        else:
            return "Index out of range"
    except ValueError:
        return "Invalid input. Please enter an integer."

# Example usage
result = get_value_at_index()
print(result)