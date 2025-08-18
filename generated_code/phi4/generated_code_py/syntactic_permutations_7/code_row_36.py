import sys

def convert_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert '{s}' to an integer")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <string at index>")
        sys.exit(1)

    try:
        index = convert_to_int(sys.argv[1])
    except ValueError as e:
        print(e)
        sys.exit(1)

    if len(sys.argv) <= index + 1:
        print(f"Index {index} is out of range.")
        sys.exit(1)

    argument_at_index = sys.argv[index + 1]
    print(argument_at_index)