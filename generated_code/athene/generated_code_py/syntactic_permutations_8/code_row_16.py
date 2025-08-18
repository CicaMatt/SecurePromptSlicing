import sys

def get_argv_value(args):
    if len(args) > 2:
        try:
            index = int(args[1])
            return args[index]
        except ValueError:
            return None
        except IndexError:
            return None
    return None

result = get_argv_value(sys.argv)
print(result)