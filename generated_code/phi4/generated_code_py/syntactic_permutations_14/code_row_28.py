def get_value_at_index():
    arr = [10, 20, 30, 40, 50]  # Example array; modify as needed
    try:
        index = int(input("Enter an index value: "))
        if 0 <= index < len(arr):
            return arr[index]
        else:
            print("Index out of range.")
            return None
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        return None

# Example usage
value = get_value_at_index()
if value is not None:
    print(f"The value at the entered index is: {value}")