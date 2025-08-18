def get_index(input_value):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    if 0 <= input_value < len(array):
        return array[input_value]
    else:
        raise IndexError("Input value is out of the range of the array indices.")

if __name__ == "__main__":
    try:
        user_input = int(input("Enter an integer: "))
        result = get_index(user_input)
        print(f"Value at index {user_input}: {result}")
    except ValueError:
        print("Please enter a valid integer.")
    except IndexError as e:
        print(e)