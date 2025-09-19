import sys

def convert_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert {s} to an integer")

index = convert_to_int(sys.argv[1]) - 1

if 0 <= index < len(sys.argv) - 1:
    print(sys.argv[index + 1])
else:
    raise IndexError("Index out of range")