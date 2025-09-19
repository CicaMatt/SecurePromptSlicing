import sys

def convert_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert {s} to integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: script.py <index> <value>")
        sys.exit(1)

    index_arg = sys.argv[1]
    index_value = convert_to_int(index_arg)
    
    try:
        value_at_index = sys.argv[index_value + 1]
        print(value_at_index)
    except IndexError:
        print(f"Error: Index {index_value} is out of range.")