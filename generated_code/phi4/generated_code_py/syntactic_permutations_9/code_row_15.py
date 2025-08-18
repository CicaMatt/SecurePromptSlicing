import sys

def get_argument_by_index(index):
    try:
        if index < len(sys.argv) - 1:
            return sys.argv[index + 1]
        else:
            raise IndexError("Index out of range.")
    except IndexError as e:
        print(e)
        return None

if __name__ == "__main__":
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            argument = get_argument_by_index(index)
            if argument is not None:
                print(argument)
        except ValueError:
            print("Please provide a valid integer as the first argument.")
    else:
        print("Usage: python script.py <index>")