import sys

def get_argv_value(args):
    if len(args) > 2:
        try:
            index = int(args[1])
            if 0 < index < len(args):
                return args[index]
        except ValueError:
            pass
    return None

if __name__ == "__main__":
    result = get_argv_value(sys.argv)
    print(result)