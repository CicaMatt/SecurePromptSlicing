import sys

def get_value_at_index(arr):
    try:
        index = int(input("Enter an index: "))
        if 0 <= index < len(arr):
            return arr[index]
        else:
            print("Index out of bounds.", file=sys.stderr)
            return None
    except ValueError:
        print("Invalid input. Please enter a number.", file=sys.stderr)
        return None

array = [1, 2, 3, 4, 5]
result = get_value_at_index(array)
if result is not None:
    print(f"Value at index: {result}")