def get_value_from_array():
    numbers = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index (0-4) to retrieve the value from the array: "))
        if 0 <= index < len(numbers):
            return numbers[index]
        else:
            print("Index out of range. Please enter a number between 0 and 4.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    result = get_value_from_array()
    if result is not None:
        print(f"Value at the entered index: {result}")