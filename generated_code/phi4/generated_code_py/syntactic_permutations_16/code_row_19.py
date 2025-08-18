def get_value_at_index():
    arr = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an integer: "))
        if 0 <= index < len(arr):
            return arr[index]
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

# Example usage
result = get_value_at_index()
if result is not None:
    print(f"Value at the given index: {result}")