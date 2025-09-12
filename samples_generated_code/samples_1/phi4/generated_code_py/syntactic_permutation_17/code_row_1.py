def get_value_at_index():
    try:
        arr = [10, 20, 30, 40, 50]
        idx = int(input("Enter an index: "))
        if 0 <= idx < len(arr):
            print(f"The value at index {idx} is: {arr[idx]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

get_value_at_index()