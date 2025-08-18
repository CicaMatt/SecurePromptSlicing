import sys

def get_value_at_index(arr):
    try:
        index = int(input("Enter an index: "))
        if index < 0 or index >= len(arr):
            print("Index out of range", file=sys.stderr)
            return None
        return arr[index]
    except ValueError:
        print("Invalid input, please enter a number.", file=sys.stderr)
        return None

array = [1, 2, 3, 4, 5]
result = get_value_at_index(array)
if result is not None:
    print(result)