def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example array
    try:
        idx = int(input("Enter an integer: "))
        if 0 <= idx < len(arr):
            print(arr[idx])
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

get_value_at_index()