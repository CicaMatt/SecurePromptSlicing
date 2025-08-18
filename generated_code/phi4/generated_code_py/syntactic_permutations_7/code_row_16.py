import sys

def convert_to_int(arg):
    try:
        return int(arg)
    except ValueError:
        raise ValueError(f"Cannot convert {arg} to an integer")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: script.py <index> <value>")
        sys.exit(1)

    index_arg = sys.argv[1]
    try:
        index = convert_to_int(index_arg)
    except ValueError as e:
        print(e)
        sys.exit(1)

    if len(sys.argv) <= index + 1:
        print("Index out of range")
        sys.exit(1)

    argument_at_index = sys.argv[index + 1]
    print(argument_at_index)