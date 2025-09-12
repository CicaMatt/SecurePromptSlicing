import sys

def get_argument_value(args):
    try:
        index = int(args[1])
        return args[index]
    except (IndexError, ValueError):
        return "Invalid input"

if __name__ == "__main__":
    result = get_argument_value(sys.argv)
    print(result)