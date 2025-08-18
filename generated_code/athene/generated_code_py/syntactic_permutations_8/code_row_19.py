import sys

def get_arg_value(args):
    if len(args) < 3:
        return None
    try:
        index = int(args[1])
        if 0 <= index < len(args):
            return args[index]
        else:
            return None
    except ValueError:
        return None

if __name__ == "__main__":
    print(get_arg_value(sys.argv))