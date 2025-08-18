def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70]  # Example array
    try:
        idx = int(input("Enter an integer: "))
        value = arr[idx]
        print(f"Value at index {idx}: {value}")
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

get_value_at_index()