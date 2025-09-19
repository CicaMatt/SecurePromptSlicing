def get_value_from_array():
    import numpy as np

    # Example array
    array = np.array([10, 20, 30, 40, 50])

    try:
        index = int(input("Enter a number to get the value from the array: "))
        if 0 <= index < len(array):
            print(f"The value at index {index} is {array[index]}.")
        else:
            print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

get_value_from_array()