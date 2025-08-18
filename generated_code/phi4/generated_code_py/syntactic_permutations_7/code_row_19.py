import sys

def convert_to_int(value):
    try:
        return int(value)
    except ValueError:
        raise ValueError(f"Cannot convert '{value}' to an integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: script.py <index> <string>")
        sys.exit(1)

    index_str = sys.argv[1]
    try:
        index = convert_to_int(index_str)
    except ValueError as e:
        print(e)
        sys.exit(1)

    if len(sys.argv) <= index + 1:
        print(f"No argument found at position {index}.")
        sys.exit(1)

    arg_at_index = sys.argv[index]
    print(arg_at_index)