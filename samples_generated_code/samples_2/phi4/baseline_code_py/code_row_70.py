def get_value_at_index():
    arr = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index to retrieve its value: "))
        print(f"The value at index {index} is {arr[index]}")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_at_index()