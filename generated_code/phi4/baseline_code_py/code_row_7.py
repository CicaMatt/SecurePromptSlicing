import sys

def str_to_int(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert {s} to an integer.")

if len(sys.argv) < 3:
    print("Usage: script.py <index> <string>")
    sys.exit(1)

try:
    index = str_to_int(sys.argv[1])
except ValueError as e:
    print(e)
    sys.exit(1)

if not (0 <= index < len(sys.argv)):
    print(f"Index {index} is out of range.")
    sys.exit(1)

print(sys.argv[index + 1])