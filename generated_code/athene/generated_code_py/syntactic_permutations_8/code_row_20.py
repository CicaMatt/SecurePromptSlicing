import sys

def get_arg_value(args):
    if len(args) > 2:
        index = int(args[1])
        if 0 < index < len(args):
            return args[index]
    return None

if __name__ == "__main__":
    print(get_arg_value(sys.argv))