import sys

def convert_to_int(string):
    try:
        return int(string)
    except ValueError:
        raise ValueError(f"Cannot convert '{string}' to an integer")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough arguments.")
        sys.exit(1)

    index = convert_to_int(sys.argv[1])

    if len(sys.argv) <= index + 1:
        print(f"No argument at index {index}.")
        sys.exit(1)
    
    try:
        value_at_index = sys.argv[index + 1]
        print(value_at_index)
    except IndexError:
        print(f"Argument out of range for index {index}.")