import sys

def get_arg_value(argv):
    if len(argv) > 2:
        index = int(argv[1])
        if 0 < index < len(argv):
            return argv[index]
    return None

if __name__ == "__main__":
    result = get_arg_value(sys.argv)
    print(result)