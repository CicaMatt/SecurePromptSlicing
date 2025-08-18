def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        index = int(input("Enter an integer: "))
        if 0 <= index < len(arr):
            return arr[index]
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"The value at the given index is: {result}")