import sys

def get_arg_value(args):
    if len(args) > 1 and args[1].isdigit() and int(args[1]) < len(args):
        return args[int(args[1])]
    else:
        return None

if __name__ == "__main__":
    print(get_arg_value(sys.argv))