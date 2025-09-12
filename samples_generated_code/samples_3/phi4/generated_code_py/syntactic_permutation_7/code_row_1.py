import sys

def string_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert '{s}' to an integer")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
    else:
        index = string_to_int(sys.argv[1])
        try:
            value_at_index = sys.argv[index + 1]  # Adjust for zero-based indexing
            print(value_at_index)
        except IndexError:
            print(f"Index {index} is out of range.")