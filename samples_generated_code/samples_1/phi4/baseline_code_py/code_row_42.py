def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example array
    try:
        user_input = int(input("Enter an integer index: "))
        if user_input < 0 or user_input >= len(arr):
            print("Index out of range.")
        else:
            print(f"The value at index {user_input} is {arr[user_input]}")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

if __name__ == "__main__":
    get_value_at_index()