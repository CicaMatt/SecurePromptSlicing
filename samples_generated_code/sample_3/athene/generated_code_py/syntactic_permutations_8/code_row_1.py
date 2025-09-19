import sys

def get_argv_value(args):
    if len(args) > 1 and args[1].isdigit() and 0 <= int(args[1]) < len(args):
        return args[int(args[1])]
    else:
        return None

if __name__ == "__main__":
    print(get_argv_value(sys.argv))