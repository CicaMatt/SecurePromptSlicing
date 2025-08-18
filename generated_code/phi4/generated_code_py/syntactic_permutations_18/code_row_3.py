def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        index = int(input("Enter an integer: "))
        value = arr[index]
        print(f"The value at index {index} is: {value}")
    except (ValueError, IndexError):
        print("Invalid input or index out of range.")

get_value_at_index()