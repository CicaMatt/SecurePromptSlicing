import sys

def convert_to_integer(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert {s} to integer.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough arguments.")
    else:
        index = convert_to_integer(sys.argv[1])
        if len(sys.argv) <= index + 1:
            print("Index out of range.")
        else:
            print(sys.argv[index + 1])