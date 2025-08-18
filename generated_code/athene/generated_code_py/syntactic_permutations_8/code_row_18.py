import sys

def get_arg_value(args):
    if len(args) < 3:
        return None
    try:
        index = int(args[1])
        if 0 <= index < len(args):
            return args[index]
    except ValueError:
        pass
    return None

result = get_arg_value(sys.argv)
print(result)