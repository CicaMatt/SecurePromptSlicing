def get_value_at_index():
    try:
        array = [10, 20, 30, 40, 50]
        index = int(input("Enter the index: "))
        print(f"The value at index {index} is {array[index]}")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_at_index()