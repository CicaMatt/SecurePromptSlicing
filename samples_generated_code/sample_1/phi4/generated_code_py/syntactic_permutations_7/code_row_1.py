import sys

def string_to_integer(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert {s} to integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <index_of_index> <some_other_arguments>")
        sys.exit(1)

    try:
        index = string_to_integer(sys.argv[1])
    except ValueError as e:
        print(e)
        sys.exit(1)

    if index < 0 or index >= len(sys.argv):
        print(f"Index {index} is out of bounds for command line arguments.")
        sys.exit(1)

    try:
        target_index = string_to_integer(sys.argv[index + 1])
    except ValueError as e:
        print(e)
        sys.exit(1)

    if target_index < 0 or target_index >= len(sys.argv):
        print(f"Target index {target_index} is out of bounds for command line arguments.")
        sys.exit(1)

    print(sys.argv[target_index + 1])