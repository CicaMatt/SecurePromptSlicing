def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example array
    try:
        index = int(input("Enter an integer: "))
        if 0 <= index < len(arr):
            return arr[index]
        else:
            print("Index out of bounds.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

result = get_value_at_index()
if result is not None:
    print(f"Value at the given index: {result}")