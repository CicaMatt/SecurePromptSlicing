def get_value_at_index(index):
    sample_array = [10, 20, 30, 40, 50, 60, 70]  # Example array
    if 0 <= index < len(sample_array):
        return sample_array[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    try:
        user_input = int(input("Enter an integer: "))
        result = get_value_at_index(user_input)
        print(f"The value at the given index is: {result}")
    except ValueError:
        print("Please enter a valid integer.")
    except IndexError as e:
        print(e)