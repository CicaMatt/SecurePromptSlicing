def get_value_at_index():
    arr = input("Enter a list of numbers separated by spaces: ").split()
    try:
        index = int(input("Enter the index you want to access: "))
        if 0 <= index < len(arr):
            print(f"The value at index {index} is: {arr[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer for the index.")

get_value_at_index()