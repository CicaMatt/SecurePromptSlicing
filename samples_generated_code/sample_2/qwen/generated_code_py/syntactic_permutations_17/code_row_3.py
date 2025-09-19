def get_value_at_index(arr):
    try:
        index = int(input("Enter the index: "))
        return arr[index]
    except IndexError:
        return "Index out of range."
    except ValueError:
        return "Invalid input, please enter an integer."

if __name__ == "__main__":
    array = [10, 20, 30, 40, 50]
    result = get_value_at_index(array)
    print("Value at index:", result)