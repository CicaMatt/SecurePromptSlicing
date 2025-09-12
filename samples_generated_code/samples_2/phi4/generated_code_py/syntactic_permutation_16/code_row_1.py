def get_value_at_index():
    arr = [10, 20, 30, 40, 50, 60, 70, 80]  # Example array
    try:
        index = int(input("Enter an integer: "))
        return arr[index]
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

result = get_value_at_index()
if result is not None:
    print(f"The value at the given index is {result}")