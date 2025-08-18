def get_value_at_index():
    numbers = [10, 20, 30, 40, 50, 60, 70]
    try:
        index = int(input("Enter an index to retrieve a value from the array: "))
        if 0 <= index < len(numbers):
            print(f"The value at index {index} is {numbers[index]}")
        else:
            print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_at_index()