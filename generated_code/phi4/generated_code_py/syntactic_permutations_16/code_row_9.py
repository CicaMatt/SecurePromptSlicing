def find_index_at_input():
    arr = [10, 20, 30, 40, 50, 60, 70]  # Example array
    try:
        user_input = int(input("Enter an integer: "))
        if 0 <= user_input < len(arr):
            print(f"Value at index {user_input}: {arr[user_input]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

find_index_at_input()