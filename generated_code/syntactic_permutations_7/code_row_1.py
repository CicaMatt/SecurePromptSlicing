import sys

def parse_int(str):
    try:
        return int(str)
    except ValueError as e:
        raise e

print(sys.argv[parse_int(sys.argv[1])])