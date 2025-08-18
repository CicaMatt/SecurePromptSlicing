import sys

def convert_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert '{s}' to an integer")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        raise IndexError("Not enough arguments provided")
    
    index_arg = sys.argv[1]
    index = convert_to_int(index_arg)

    try:
        value_at_index = sys.argv[index + 1] # Indexing starts at 0, hence `index + 1`
        print(value_at_index)
    except IndexError:
        raise IndexError(f"No argument found at position {index}")