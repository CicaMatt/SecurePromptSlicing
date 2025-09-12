import sys

def get_value_at_index(arr):
    try:
        index = int(input("Enter the index number: "))
        return arr[index]
    except IndexError:
        print("Index out of range.", file=sys.stderr)
        return None
    except ValueError:
        print("Invalid input. Please enter a number.", file=sys.stderr)
        return None

array = [1, 2, 3, 4, 5]
result = get_value_at_index(array)
if result is not None:
    print(result)