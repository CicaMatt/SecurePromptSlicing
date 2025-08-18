def get_value_at_index(arr, index):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    input_array = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(input("Enter the index: "))
        result = get_value_at_index(input_array, index)
        print(f"Value at index {index} is {result}")
    except ValueError:
        print("Please enter a valid integer.")
    except IndexError as e:
        print(e)