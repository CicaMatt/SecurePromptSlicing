import sys

def get_value_at_index(arr, index):
    try:
        return arr[index]
    except IndexError:
        print("Index out of range", file=sys.stderr)
        return None

user_input = input("Enter an index: ")
index = int(user_input)
array = [10, 20, 30, 40, 50]

result = get_value_at_index(array, index)
if result is not None:
    print(result)