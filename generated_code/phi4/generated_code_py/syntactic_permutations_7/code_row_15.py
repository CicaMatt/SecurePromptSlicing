import sys

def convert_string_to_integer(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert {s} to integer")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <string>")
        sys.exit(1)

    index_str = sys.argv[1]
    try:
        index = convert_string_to_integer(index_str)
    except ValueError as e:
        print(e)
        sys.exit(1)

    if len(sys.argv) <= index + 2:
        print(f"No argument at position {index}")
        sys.exit(1)

    value_at_index = sys.argv[index + 2]
    print(value_at_index)