def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70]  # Example array
    index = int(input("Enter an integer: "))
    
    if 0 <= index < len(arr):
        print(f"Value at index {index}: {arr[index]}")
    else:
        print("Index out of range.")

get_value_at_index()