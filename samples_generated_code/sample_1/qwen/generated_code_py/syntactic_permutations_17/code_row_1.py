def get_value_at_index():
    try:
        numbers = [10, 20, 30, 40, 50]
        index = int(input("Enter an index: "))
        print(numbers[index])
    except IndexError:
        print("Index is out of range.")
    except ValueError:
        print("Please enter a valid integer.")

get_value_at_index()