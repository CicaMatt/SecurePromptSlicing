def get_value_at_index():
    numbers = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter the index: "))
        print(numbers[index])
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

get_value_at_index()