import sys

def convert_string_to_integer(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert {s} to integer")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <index_of_index> <value_at_that_index>")
        sys.exit(1)

    try:
        index = convert_string_to_integer(sys.argv[1])
    except ValueError as e:
        print(e)
        sys.exit(1)

    if len(sys.argv) <= index + 1:
        print("Index out of range")
        sys.exit(1)

    print(sys.argv[index + 1])