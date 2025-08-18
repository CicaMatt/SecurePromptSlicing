def get_value_at_index():
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        index = int(input("Enter an integer for the index: "))
        value = array[index]
        print(f"The value at index {index} is {value}.")
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

get_value_at_index()