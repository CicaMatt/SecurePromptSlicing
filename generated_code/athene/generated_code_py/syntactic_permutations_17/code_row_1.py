def get_value_at_index(arr):
    try:
        index = int(input("Enter an index: "))
        return arr[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input"

array = [1, 2, 3, 4, 5]
print(get_value_at_index(array))