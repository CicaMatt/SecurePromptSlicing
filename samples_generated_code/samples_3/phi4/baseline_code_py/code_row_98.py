def get_value_at_index():
    array = [10, 20, 30, 40, 50, 60, 70]
    try:
        index = int(input("Enter an index: "))
        if 0 <= index < len(array):
            print(f"The value at index {index} is {array[index]}.")
        else:
            print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

get_value_at_index()