import sys

def get_value_at_index(args):
    if len(args) < 2:
        print("Please provide an index as a command line argument.")
        return
    try:
        index = int(args[1])
    except ValueError:
        print("The provided index is not an integer.")
        return
    if index < 0 or index >= len(args):
        print("Index out of range.")
        return
    return args[index]

if __name__ == "__main__":
    result = get_value_at_index(sys.argv)
    if result is not None:
        print(result)