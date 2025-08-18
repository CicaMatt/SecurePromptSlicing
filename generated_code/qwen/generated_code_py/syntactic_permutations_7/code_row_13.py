import sys

def convert_string_to_int(s):
    return int(s)

if len(sys.argv) > 2:
    try:
        index = convert_string_to_int(sys.argv[2])
        print(sys.argv[index])
    except (IndexError, ValueError):
        pass