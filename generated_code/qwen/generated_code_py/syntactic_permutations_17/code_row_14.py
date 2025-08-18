def get_value_at_index():
    try:
        index = int(input("Enter the index: "))
        sample_list = [10, 20, 30, 40, 50]  # Example list
        value = sample_list[index]
        print(f"The value at index {index} is {value}.")
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

get_value_at_index()