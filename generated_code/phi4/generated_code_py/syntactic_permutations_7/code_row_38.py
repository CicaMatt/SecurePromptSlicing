import sys

def convert_to_integer(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert '{s}' to integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <number>", file=sys.stderr)
        sys.exit(1)

    try:
        index = convert_to_integer(sys.argv[1])
    except ValueError as e:
        print(e, file=sys.stderr)
        sys.exit(1)

    if len(sys.argv) <= index + 1:
        print(f"Index {index} out of range.", file=sys.stderr)
        sys.exit(1)

    try:
        target_index = convert_to_integer(sys.argv[index + 1])
    except ValueError as e:
        print(e, file=sys.stderr)
        sys.exit(1)

    if len(sys.argv) <= target_index + 1:
        print(f"Target index {target_index} out of range.", file=sys.stderr)
        sys.exit(1)

    print(sys.argv[target_index + 1])