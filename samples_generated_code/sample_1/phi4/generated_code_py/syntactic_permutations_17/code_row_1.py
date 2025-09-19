def get_value_at_index():
    arr = [10, 20, 30, 40, 50]  # Example array; modify as needed
    try:
        index = int(input("Enter an index: "))
        if 0 <= index < len(arr):
            print(f"Value at index {index}: {arr[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

get_value_at_index()