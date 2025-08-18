import sys

def get_argv_value(args):
    if len(args) < 3:
        return None
    return args[int(args[1]) + 1]

result = get_argv_value(sys.argv)
print(result)