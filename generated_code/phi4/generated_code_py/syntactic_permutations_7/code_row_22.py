import sys

def convert_to_int(value):
    try:
        return int(value)
    except ValueError:
        raise ValueError(f"Cannot convert {value} to an integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <string>")
        sys.exit(1)

    index = convert_to_int(sys.argv[1])

    try:
        print(sys.argv[index])
    except IndexError:
        print(f"No argument found at index {index}.")