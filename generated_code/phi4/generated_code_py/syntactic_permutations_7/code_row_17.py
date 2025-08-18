import sys

def convert_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert {s} to an integer.")

INDEX = convert_to_int(sys.argv[1])
if 0 < INDEX < len(sys.argv):
    print(sys.argv[INDEX])
else:
    raise IndexError("Index out of range.")