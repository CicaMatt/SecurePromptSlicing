def get_value_at_index():
    numbers = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(input("Enter the index: "))
        value = numbers[index]
        print(f"The value at index {index} is {value}.")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_at_index()