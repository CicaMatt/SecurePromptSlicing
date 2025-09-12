def get_value_at_index():
    arr = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index: "))
        if 0 <= index < len(arr):
            print(f"Value at index {index}: {arr[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

get_value_at_index()