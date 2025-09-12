import sys

def convert_string_to_int(string):
    try:
        return int(string)
    except ValueError:
        raise ValueError(f"Cannot convert '{string}' to an integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: script.py <index-of-index> <input-string>")
        sys.exit(1)

    try:
        index_of_index = convert_string_to_int(sys.argv[1])
    except ValueError as e:
        print(e)
        sys.exit(1)

    if not (0 <= index_of_index < len(sys.argv)):
        print(f"Index {index_of_index} is out of range.")
        sys.exit(1)

    try:
        target_index = convert_string_to_int(sys.argv[index_of_index + 1])
    except ValueError as e:
        print(e)
        sys.exit(1)

    if not (0 <= target_index < len(sys.argv)):
        print(f"Target index {target_index} is out of range.")
        sys.exit(1)

    print(sys.argv[target_index + 1])