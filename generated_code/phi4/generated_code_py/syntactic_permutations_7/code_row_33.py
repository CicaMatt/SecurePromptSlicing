import sys

def string_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError("The input cannot be converted to an integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: script.py <index> <value>")
        sys.exit(1)

    index_arg = string_to_int(sys.argv[1])
    
    try:
        value_at_index = sys.argv[index_arg]
        print(f"Value at index {index_arg}: {value_at_index}")
    except IndexError:
        print(f"No argument found at the specified index: {index_arg}")