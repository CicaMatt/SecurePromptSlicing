def get_value_at_index():
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        index = int(input("Enter an integer: "))
        if 0 <= index < len(array):
            print(array[index])
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

get_value_at_index()