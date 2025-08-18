import sys

def convert_string_to_int(string):
    try:
        return int(string)
    except ValueError:
        raise ValueError(f"Cannot convert '{string}' to an integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
        sys.exit(1)

    index = convert_string_to_int(sys.argv[1])

    if index < 2 or index >= len(sys.argv):
        print(f"Index {index} is out of range for the command line arguments.")
        sys.exit(1)

    print(sys.argv[index])