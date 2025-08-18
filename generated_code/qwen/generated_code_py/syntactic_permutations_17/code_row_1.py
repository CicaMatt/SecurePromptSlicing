def get_value_at_index():
    arr = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(input("Enter an index: "))
        value = arr[index]
        print(f"The value at index {index} is {value}.")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter a numeric index.")

get_value_at_index()