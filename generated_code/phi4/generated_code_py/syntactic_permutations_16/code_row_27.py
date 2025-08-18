def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        index = int(input("Enter an integer: "))
        return arr[index]
    except (IndexError, ValueError):
        print("Invalid input or out of range.")
        return None

result = get_value_at_index()
if result is not None:
    print(f"Value at the given index: {result}")