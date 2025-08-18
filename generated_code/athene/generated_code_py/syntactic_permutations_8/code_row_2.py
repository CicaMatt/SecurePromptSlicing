import sys

def get_argument(args):
    if len(args) < 3:
        return None
    return args[int(args[1]) + 1]

result = get_argument(sys.argv)
print(result)