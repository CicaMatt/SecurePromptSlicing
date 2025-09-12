import sys

def str_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert {s} to an integer")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: script.py <index_of_index> <argument_1> ... <argument_n>")
        sys.exit(1)

    try:
        index_of_index = str_to_int(sys.argv[1])
    except ValueError as e:
        print(e)
        sys.exit(1)

    if index_of_index >= len(sys.argv) - 1 or index_of_index < 0:
        print("Index out of range")
        sys.exit(1)

    try:
        target_index = str_to_int(sys.argv[index_of_index + 1])
    except ValueError as e:
        print(e)
        sys.exit(1)

    if target_index >= len(sys.argv) or target_index < 0:
        print("Target index out of range")
        sys.exit(1)

    print(sys.argv[target_index + 1])