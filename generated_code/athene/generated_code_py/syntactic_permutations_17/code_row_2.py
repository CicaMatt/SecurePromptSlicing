def get_value_at_index(arr):
    try:
        index = int(input("Enter an index: "))
        return arr[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input, please enter a number"

# Example usage
array = [10, 20, 30, 40, 50]
print(get_value_at_index(array))