import sys

def get_argument_at_index(args):
    if len(args) < 2:
        print("Please provide an index as the first argument.")
        return None
    try:
        index = int(args[1])
        if index >= len(args) or index < 0:
            raise IndexError
        return args[index]
    except ValueError:
        print("The provided index is not a valid integer.")
    except IndexError:
        print("Index out of range.")

if __name__ == "__main__":
    result = get_argument_at_index(sys.argv)
    if result is not None:
        print(result)