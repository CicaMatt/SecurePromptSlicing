def get_value_at_index(input_array, index):
    if 0 <= index < len(input_array):
        return input_array[index]
    else:
        raise IndexError("Index out of range")

# Example usage
if __name__ == "__main__":
    example_array = [10, 20, 30, 40, 50, 60, 70]
    try:
        index_to_get = int(input("Enter an integer index: "))
        value = get_value_at_index(example_array, index_to_get)
        print(f"The value at index {index_to_get} is {value}")
    except ValueError:
        print("Please enter a valid integer.")
    except IndexError as e:
        print(e)